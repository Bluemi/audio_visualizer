#include "Generator.hpp"

class GeneratorExtractor
{
	public:
		GeneratorExtractor(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
			: _pool(pool), _algorithm_factory(algorithm_factory)
		{}

		Generator operator()(const BeatEventSpecification& spec)
		{
			return BeatDataGenerator(_pool, _algorithm_factory, spec.get_min_amplitude());
		}

		Generator operator()(const AudioEventSpecification& spec)
		{
			return AudioDataGenerator(_pool, _algorithm_factory, spec.get_filename());
		}

		Generator operator()(const WriteEventSpecification& spec)
		{
			return WriteDataGenerator(_pool, _algorithm_factory, spec.get_output_filename());
		}
	private:
		essentia::Pool* _pool;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
};

Generator build_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory,  const EventSpecification& specification)
{
	GeneratorExtractor generator_extractor(pool, algorithm_factory);
	return std::visit(generator_extractor, specification);
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

void compute_generator(Generator& generator)
{
	std::visit([](auto& g) { g.compute(); },
			   generator);
}
