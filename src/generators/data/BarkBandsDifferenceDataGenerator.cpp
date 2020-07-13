#include "BarkBandsDifferenceDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"
#include "../../misc/Misc.hpp"

BarkBandsDifferenceDataGenerator::BarkBandsDifferenceDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void BarkBandsDifferenceDataGenerator::compute() {
	std::cout << "Calculating BarkBandsDifferences... " << std::flush;

	misc::Matrix bark_bands = _pool->value<misc::Matrix>(data_identifier::BARK_BANDS);
	misc::Matrix transposed = misc::transpose(bark_bands);
	misc::Matrix changes = misc::calculate_changes(transposed);

	for (const std::vector<essentia::Real>& vec : changes) {
		_pool->add(data_identifier::BARK_BANDS_DIFFERENCES, vec);
	}

	std::cout << "Done." << std::endl;
}
