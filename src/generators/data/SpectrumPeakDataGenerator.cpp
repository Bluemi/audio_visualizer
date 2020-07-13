#include "SpectrumPeakDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

SpectrumPeakDataGenerator::SpectrumPeakDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void SpectrumPeakDataGenerator::compute() {
	std::cout << "Calculating SpectrumPeaks... " << std::flush;

	std::vector<std::vector<float>> spectren = _pool->value<std::vector<std::vector<float>>>(data_identifier::SPECTRUM);

	essentia::standard::Algorithm* spec_peaks = _algorithm_factory->create("SpectralPeaks");

	std::vector<float> frequencies, magnitudes;

	spec_peaks->output("frequencies").set(frequencies);
	spec_peaks->output("magnitudes").set(magnitudes);

	for (const std::vector<float>& spectrum : spectren) {
		spec_peaks->input("spectrum").set(spectrum);
		spec_peaks->compute();

		_pool->add(data_identifier::SPECTRUM_PEAKS_FREQUENCIES, frequencies);
		_pool->add(data_identifier::SPECTRUM_PEAKS_MAGNITUDES, magnitudes);
	}

	std::cout << "Done." << std::endl;
}
