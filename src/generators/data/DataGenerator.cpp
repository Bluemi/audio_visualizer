#include "DataGenerator.hpp"

class GeneratorCreator
{
	public:
		GeneratorCreator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
			: _pool(pool), _algorithm_factory(algorithm_factory)
		{}

		DataGenerator operator()(const BeatDataSpecification& spec)
		{
			return BeatDataGenerator(_pool, _algorithm_factory, spec.get_min_amplitude());
		}

		DataGenerator operator()(const AudioDataSpecification&)
		{
			return AudioDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const WriteDataSpecification& spec)
		{
			return WriteDataGenerator(_pool, _algorithm_factory, spec.get_output_filename());
		}
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
};

DataGenerator create_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const DataSpecification& specification)
{
	GeneratorCreator generator_creator(pool, algorithm_factory);
	return std::visit(generator_creator, specification);
}

/*
class
{
	public:
		void operator()(BeatDataGenerator& generator)
		{
			generator.compute();
		}
		void operator()(AudioDataGenerator& generator)
		{
			generator.compute();
		}
} _generator_computer;
*/

void compute_generator(DataGenerator& generator)
{
	std::visit([](auto& g) { g.compute(); }, generator);
}
