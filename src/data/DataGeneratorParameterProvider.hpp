#ifndef __DATAGENERATORPARAMETERPROVIDER_CLASS__
#define __DATAGENERATORPARAMETERPROVIDER_CLASS__

#include <string>

#include "../generators/data/DataGenerator.hpp"

class DataGeneratorParameterProvider
{
	public:
		DataGeneratorParameterProvider(const std::string& filename);
		void provide(DataGenerator* data_generator);

		void operator()(BeatDataGenerator& bdg);
		void operator()(AudioDataGenerator& bdg);
		void operator()(WriteDataGenerator& bdg);
	private:
		std::string _filename;
};

#endif
