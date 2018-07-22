#include "WriteDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

WriteDataGenerator::WriteDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const std::string& output_filename)
	: _pool(pool), _algorithm_factory(algorithm_factory), _output_filename(output_filename)
{}

void WriteDataGenerator::compute()
{
	essentia::standard::Algorithm* output = _algorithm_factory->create("YamlOutput",
																	   "filename", _output_filename);

	essentia::Pool p;
	p.set("highlevel.tick_positions", _pool->value<std::vector<essentia::Real>>(data_identifier::TICK_POSITIONS));
	output->input("pool").set(p);
	output->compute();

	delete output;
}
