#include "DataGeneratorParameterProvider.hpp"

DataGeneratorParameterProvider::DataGeneratorParameterProvider(const std::string& filename)
	: _filename(filename)
{}

void DataGeneratorParameterProvider::operator()(TickDataGenerator&)
{}

void DataGeneratorParameterProvider::operator()(AudioDataGenerator& adg)
{
	adg.set_filename(_filename);
}

void DataGeneratorParameterProvider::operator()(WriteDataGenerator&)
{}

void DataGeneratorParameterProvider::operator()(FrameDataGenerator&)
{}

void DataGeneratorParameterProvider::operator()(WindowedFrameDataGenerator&)
{}

void DataGeneratorParameterProvider::operator()(BarkBandsDataGenerator&)
{}

void DataGeneratorParameterProvider::operator()(SpectrumDataGenerator&)
{}

void DataGeneratorParameterProvider::provide(DataGenerator* data_generator)
{
	std::visit(*this, *data_generator);
}
