#ifndef __WRITEDATAGENERATOR_CLASS__
#define __WRITEDATAGENERATOR_CLASS__

#include <essentia/algorithmfactory.h>
#include <essentia/pool.h>

class WriteDataGenerator
{
	public:
		WriteDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const std::string& output_filename);
		void compute();
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
		std::string _output_filename;
};

#endif
