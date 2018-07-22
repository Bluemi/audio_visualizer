#include "SpectrumDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

SpectrumDataGenerator::SpectrumDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void SpectrumDataGenerator::compute()
{
	essentia::standard::Algorithm* spec = _algorithm_factory->create("Spectrum");

	std::vector<essentia::Real> spectrum;
	spec->output("spectrum").set(spectrum);

	const std::vector<std::vector<essentia::Real>>& windowed_frames = _pool->value<std::vector<std::vector<essentia::Real>>>(data_identifier::WINDOWED_FRAMES);

	std::cout << "Calculating Spectrum... " << std::flush;

	for (const std::vector<essentia::Real>& windowed_frame : windowed_frames)
	{
		spec->input("frame").set(windowed_frame);
		spec->compute();
		_pool->add(data_identifier::SPECTRUM, spectrum);
	}

	std::cout << "Done." << std::endl;

	delete spec;
}
