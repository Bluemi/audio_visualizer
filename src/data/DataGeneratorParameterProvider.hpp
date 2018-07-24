#ifndef __DATAGENERATORPARAMETERPROVIDER_CLASS__
#define __DATAGENERATORPARAMETERPROVIDER_CLASS__

#include <string>

#include "../generators/data/DataGenerator.hpp"

class DataGeneratorParameterProvider
{
	public:
		DataGeneratorParameterProvider(const std::string& filename);
		void provide(DataGenerator* data_generator);

		template<typename DataGeneratorType>
		void operator()(DataGeneratorType&)
		{}

		void operator()(AudioDataGenerator& dg);
	private:
		std::string _filename;
};

#endif
