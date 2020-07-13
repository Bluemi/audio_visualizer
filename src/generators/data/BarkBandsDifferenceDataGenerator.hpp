#ifndef __BARKBANDSDIFFERENCEDATAGENERATOR_CLASS__
#define __BARKBANDSDIFFERENCEDATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class BarkBandsDifferenceDataGenerator {
	public:
		BarkBandsDifferenceDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
};

#endif
