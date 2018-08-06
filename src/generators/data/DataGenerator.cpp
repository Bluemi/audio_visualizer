#include "DataGenerator.hpp"

class GeneratorCreator
{
	public:
		GeneratorCreator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
			: _pool(pool), _algorithm_factory(algorithm_factory)
		{}

		DataGenerator operator()(const AudioDataSpecification&)
		{
			return AudioDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const FrameDataSpecification&)
		{
			return FrameDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const WindowedFrameDataSpecification&)
		{
			return WindowedFrameDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const SpectrumDataSpecification&)
		{
			return SpectrumDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const BarkBandsDataSpecification&)
		{
			return BarkBandsDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const BarkBandsDifferenceDataSpecification&)
		{
			return BarkBandsDifferenceDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const SpectrumPeakDataSpecification&)
		{
			return SpectrumPeakDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const PitchClassProfileDataSpecification&)
		{
			return PitchClassProfileDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const ChordDataSpecification&)
		{
			return ChordDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const ArousalDataSpecification&)
		{
			return ArousalDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const ValenceDataSpecification&)
		{
			return ValenceDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const PartsDataSpecification&)
		{
			return PartsDataGenerator(_pool, _algorithm_factory);
		}

		DataGenerator operator()(const TickDataSpecification& spec)
		{
			return TickDataGenerator(_pool, _algorithm_factory, spec.get_min_amplitude());
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

void compute_generator(DataGenerator& generator)
{
	std::visit([](auto& g) { g.compute(); }, generator);
}
