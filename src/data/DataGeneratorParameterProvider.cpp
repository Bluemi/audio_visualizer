#include "DataGeneratorParameterProvider.hpp"

DataGeneratorParameterProvider::DataGeneratorParameterProvider(const std::string& filename)
	: _filename(filename)
{}

void DataGeneratorParameterProvider::operator()(AudioDataGenerator& adg)
{
	adg.set_filename(_filename);
}

void DataGeneratorParameterProvider::provide(DataGenerator* data_generator)
{
	std::visit(*this, *data_generator);
}
