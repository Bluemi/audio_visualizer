#ifndef __SPECTRUMPEAKDATAGENERATOR_CLASS__
#define __SPECTRUMPEAKDATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class SpectrumPeakDataGenerator {
	public:
		SpectrumPeakDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
};

#endif
