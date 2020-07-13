#ifndef __PARTSDATAGENERATOR_CLASS__
#define __PARTSDATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class PartsDataGenerator {
	public:
		PartsDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
};

#endif
