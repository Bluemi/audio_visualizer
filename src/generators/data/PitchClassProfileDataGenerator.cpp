#include "PitchClassProfileDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

PitchClassProfileDataGenerator::PitchClassProfileDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void PitchClassProfileDataGenerator::compute() {
	std::cout << "Calculating PitchClassProfiles... " << std::flush;

	std::vector<std::vector<float>> frequencies = _pool->value<std::vector<std::vector<float>>>(data_identifier::SPECTRUM_PEAKS_FREQUENCIES);
	std::vector<std::vector<float>> magnitudes = _pool->value<std::vector<std::vector<float>>>(data_identifier::SPECTRUM_PEAKS_MAGNITUDES);

	std::vector<float> pitch_class_profile;
	std::vector<std::vector<float>> pitch_class_profiles;

	essentia::standard::Algorithm* pitch_class_profiler = _algorithm_factory->create("HPCP");

	pitch_class_profiler->output("hpcp").set(pitch_class_profile);

	if (frequencies.size() == magnitudes.size()) {
		for (unsigned int i = 0; i < frequencies.size(); i++) {
			pitch_class_profiler->input("frequencies").set(frequencies[i]);
			pitch_class_profiler->input("magnitudes").set(magnitudes[i]);

			pitch_class_profiler->compute();

			pitch_class_profiles.push_back(pitch_class_profile);
		}

		// normalize pitch_class_profiles
		double sum = 0.f;
		for (const std::vector<float>& v : pitch_class_profiles)
			for (float f : v)
				sum += f;

		float avg = sum / (pitch_class_profiles.size() * pitch_class_profiles[0].size());

		for (std::vector<float>& vec : pitch_class_profiles)
			for (float& f : vec)
				f = std::min(f / avg, 2.f);

		for (const std::vector<float>& vec : pitch_class_profiles)
			_pool->add(data_identifier::PITCH_CLASS_PROFILES, vec);

		std::cout << "Done." << std::endl;
	} else {
		std::cout << "\nERROR: PitchClassProfileDataGenerator::compute(): frequencies.size() != magnitudes.size()" << std::endl;
	}
}
