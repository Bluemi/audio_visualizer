#ifndef __TICKDATAGENERATOR_CLASS__
#define __TICKDATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class TickDataGenerator {
	public:
		TickDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, float min_amplitude);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
		float _min_amplitude;
};

#endif
