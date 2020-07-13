#include "ChordDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

ChordDataGenerator::ChordDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void ChordDataGenerator::compute() {
	std::cout << "Analysing Chords... " << std::flush;

	essentia::standard::Algorithm* chord_detection = _algorithm_factory->create("ChordsDetection");

	std::vector<std::vector<float>> pitch_class_profiles = _pool->value<std::vector<std::vector<float>>>(data_identifier::PITCH_CLASS_PROFILES);

	std::vector<std::string> chords;
	std::vector<float> chord_strength;

	chord_detection->input("pcp").set(pitch_class_profiles);
	chord_detection->output("chords").set(chords);
	chord_detection->output("strength").set(chord_strength);

	chord_detection->compute();

	_pool->set(data_identifier::CHORDS, chords);
	_pool->set(data_identifier::CHORD_STRENGTHS, chord_strength);

	std::cout << "Done." << std::endl;
}
