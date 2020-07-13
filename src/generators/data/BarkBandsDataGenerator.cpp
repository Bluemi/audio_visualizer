#include "BarkBandsDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

BarkBandsDataGenerator::BarkBandsDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void BarkBandsDataGenerator::compute() {
	std::cout << "Calculating Bark Bands... " << std::flush;

	essentia::standard::Algorithm* bark_bands = _algorithm_factory->create("BarkBands");

	const std::vector<std::vector<essentia::Real>>& spectren = _pool->value<std::vector<std::vector<essentia::Real>>>(data_identifier::SPECTRUM);

	std::vector<essentia::Real> bands;
	bark_bands->output("bands").set(bands);

	for (const std::vector<essentia::Real>& spectrum : spectren)
	{
		bark_bands->input("spectrum").set(spectrum);
		bark_bands->compute();
		_pool->add(data_identifier::BARK_BANDS, bands);
	}

	delete bark_bands;

	std::cout << "Done." << std::endl;
}
