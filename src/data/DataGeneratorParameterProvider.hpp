#ifndef __DATAGENERATORPARAMETERPROVIDER_CLASS__
#define __DATAGENERATORPARAMETERPROVIDER_CLASS__

#include <string>

#include "../generators/data/DataGenerator.hpp"

class DataGeneratorParameterProvider
{
	public:
		DataGeneratorParameterProvider(const std::string& filename);
		void provide(DataGenerator* data_generator);

		void operator()(TickDataGenerator& dg);
		void operator()(AudioDataGenerator& dg);
		void operator()(WriteDataGenerator& dg);
		void operator()(FrameDataGenerator& dg);
		void operator()(WindowedFrameDataGenerator& dg);
		void operator()(BarkBandsDataGenerator& dg);
		void operator()(SpectrumDataGenerator& dg);
	private:
		std::string _filename;
};

#endif
