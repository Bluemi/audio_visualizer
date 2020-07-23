#include "ArousalDataGenerator.hpp"

#include "../../misc/Misc.hpp"
#include "../../data/DataIdentifier.hpp"
#include "misc/Misc.hpp"

ArousalDataGenerator::ArousalDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

std::vector<float> calculate_loudness_time_line(const misc::Matrix& bark_bands_differences) {
	std::vector<float> loudness_time_line;
	const unsigned int num_frames = bark_bands_differences[0].size();
	loudness_time_line.reserve(num_frames);

	for (unsigned int time_index = 0; time_index < num_frames; time_index++) {
		float loudness_change = 0.f;
		for (unsigned int frequency_index = 0; frequency_index < bark_bands_differences.size(); frequency_index++) {
			loudness_change += std::abs(bark_bands_differences[frequency_index][time_index]);
		}
		loudness_time_line.push_back(loudness_change);
	}

	return loudness_time_line;
}

const float AROUSAL_FACTOR = 0.75f;

std::vector<float> calc_arousal(const std::vector<float>& time_line) {
	float x = 0.f;

	std::vector<float> arousals;
	arousals.reserve(time_line.size());

	for (float loudness_change : time_line) {
		x = x*0.98f;
		if (x < loudness_change)
			x = loudness_change;

		float arousal = 0.f;
		if (loudness_change > 0.f)
			arousal = loudness_change;
		else
			arousal = x * -loudness_change * 20.f;
		arousals.push_back(std::pow(arousal, 1.f/1.5f)*AROUSAL_FACTOR);
	}

	return arousals;
}

const float MIN_LOUDNESS = 0.15f;
const float ACCELERATION = 0.015f;

std::vector<float> calculate_arousal(misc::Matrix bark_bands_differences) {
	float max_loudness_change = 0.f;
	for (const std::vector<float>& time_line : bark_bands_differences)
		for (float loudness_change : time_line)
			max_loudness_change = std::max(max_loudness_change, loudness_change);

	max_loudness_change = std::max(max_loudness_change, MIN_LOUDNESS);

	for (std::vector<float>& time_line : bark_bands_differences)
		for (float& loudness_change : time_line)
			loudness_change = loudness_change / max_loudness_change;

	std::vector<float> merged_arousals;

	for (const std::vector<float>& time_line : bark_bands_differences) {
		std::vector<float> arousal = calc_arousal(time_line);
		if (merged_arousals.size() == 0) {
			merged_arousals = arousal;
		} else {
			for (unsigned int i = 0; i < merged_arousals.size(); i++)
				merged_arousals[i] += arousal[i];
		}
	}

	std::vector<float> arousals;
	float arousal = 0.f;

	for (float f : merged_arousals) {
		f = std::pow(f, 1.0/2.0);

		float arousal_acceleration = (f - arousal) * ACCELERATION;
		arousal += arousal_acceleration;
		arousals.push_back(arousal);
	}

	return arousals;
}

void ArousalDataGenerator::compute() {
	std::cout << "Calculating Arousal Data... " << std::flush;

	const misc::Matrix& bark_bands_differences = _pool->value<misc::Matrix>(data_identifier::BARK_BANDS_DIFFERENCES);
	std::vector<float> arousal_timeline = calculate_arousal(bark_bands_differences);

	_pool->set(data_identifier::AROUSAL_TIMELINE, arousal_timeline);

	std::cout << "Done." << std::endl;
}
