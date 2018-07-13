#ifndef __AUDIODATAGENERATOR_CLASS__
#define __AUDIODATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class AudioDataGenerator
{
	public:
		AudioDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const std::string& filename);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
		std::string _filename;

};

#endif
