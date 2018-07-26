#include "ValenceDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

ValenceDataGenerator::ValenceDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

// translate a Chord Identifier into a numeric value
unsigned int chord_to_int(const std::string& chord)
{
	unsigned int tone = 0;
	switch (chord[0])
	{
		case 'A':
			tone = 0;
			break;
		case 'B':
			tone = 2;
			break;
		case 'C':
			tone = 3;
			break;
		case 'D':
			tone = 5;
			break;
		case 'E':
			tone = 7;
			break;
		case 'F':
			tone = 8;
			break;
		case 'G':
			tone = 10;
			break;
		default:
			std::cout << "ERROR: unknown chord: \"" << chord << "\"" << std::endl;
			break;
	}

	if (chord.size() > 1)
		if (chord[1] == '#')
			tone++;

	return tone;
}

// The Priority of the Terz over the Sexte
const float TERZ_PRIO = 0.7f;

// Gets the probability of this chord to be a major chord
float get_major_probability(const std::string& chord, const std::vector<float>& pcp)
{
	unsigned int base_tone = chord_to_int(chord);
	unsigned int little_terz_tone = (base_tone + 3) % 12;
	unsigned int big_terz_tone = (base_tone + 4) % 12;
	unsigned int little_sixt_tone = (base_tone + 8) % 12;
	unsigned int big_sixt_tone = (base_tone + 9) % 12;

	float dur_propability_terz = 0.f;
	float dur_propability_sixt = 0.f;

	float little_terz_amp = pcp[little_terz_tone] * 1.4f;
	float big_terz_amp = pcp[big_terz_tone];
	float little_sixt_amp = pcp[little_sixt_tone] * 1.4f;
	float big_sixt_amp = pcp[big_sixt_tone];

	if (std::max(big_terz_amp, little_terz_amp) > 0.1f)
		dur_propability_terz = (big_terz_amp / (big_terz_amp + little_terz_amp))*2 - 1;
	if (std::max(big_sixt_amp, little_sixt_amp) > 0.1f)
		dur_propability_sixt = (big_sixt_amp / (big_sixt_amp + little_sixt_amp))*2 - 1;

	dur_propability_terz *= std::max(little_terz_amp, big_terz_amp);
	dur_propability_sixt *= std::max(little_sixt_amp, big_sixt_amp);

	return (dur_propability_terz*TERZ_PRIO + dur_propability_sixt*(1-TERZ_PRIO)); //-0.1f;
}

float sqr(float v) { return v*v; }

const float ACCELERATION = 0.01f;

std::vector<float> calculate_valence(const std::vector<std::string>& chords, const std::vector<float>& chord_strengths, const std::vector<std::vector<float>>& pitch_class_profiles)
{
	float dur_ratio = 0.f;

	std::vector<float> valence_timeline;

	for (unsigned int i = 0; i < chords.size(); i++)
	{
		const float major_propability = get_major_probability(chords[i], pitch_class_profiles[i]);
		float acceleration = major_propability - dur_ratio;

		// if chord is identifiable
		if (chord_strengths[i] > 0)
		{
			acceleration *= sqr(chord_strengths[i]);
		}
		else // move to 0.0 with lower acceleration (0.2)
		{
			acceleration = (0.0f - dur_ratio)*0.2;
		}
		acceleration *= ACCELERATION;
		dur_ratio += acceleration;
		const float chord_tmp = (dur_ratio+1.f)/2.f; // normalize from [-1, 1] -> [0, 1]
		valence_timeline.push_back(chord_tmp);
	}

	return valence_timeline;
}

void ValenceDataGenerator::compute()
{
	std::cout << "Calculating Valence Data... " << std::flush;

	std::vector<std::string> chords = _pool->value<std::vector<std::string>>(data_identifier::CHORDS);
	std::vector<float> chord_strengths = _pool->value<std::vector<float>>(data_identifier::CHORD_STRENGTHS);
	std::vector<std::vector<float>> pitch_class_profiles = _pool->value<std::vector<std::vector<float>>>(data_identifier::PITCH_CLASS_PROFILES);

	if ((chords.size() == chord_strengths.size()) && (chords.size() == pitch_class_profiles.size()))
	{
		std::vector<float> valence_timeline = calculate_valence(chords, chord_strengths, pitch_class_profiles);

		_pool->set(data_identifier::VALENCE_TIMELINE, valence_timeline);

		std::cout << "Done." << std::endl;
	} else {
		std::cout << "ERROR: ValenceDataGenerator::compute(): chords.size() != chord_strengths.size() or chords.size() != pitch_class_profiles.size()" << std::endl;
	}
}
