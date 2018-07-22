#ifndef __DATAGENERATOR_CLASS__
#define __DATAGENERATOR_CLASS__

#include <variant>

#include <essentia/pool.h>

#include "../../data/DataSpecification.hpp"
#include "TickDataGenerator.hpp"
#include "AudioDataGenerator.hpp"
#include "WriteDataGenerator.hpp"
#include "BarkBandsDataGenerator.hpp"
#include "SpectrumDataGenerator.hpp"
#include "FrameDataGenerator.hpp"
#include "WindowedFrameDataGenerator.hpp"

using DataGenerator = std::variant<AudioDataGenerator,
	  							   TickDataGenerator,
								   WriteDataGenerator,
								   BarkBandsDataGenerator,
								   SpectrumDataGenerator,
								   FrameDataGenerator,
								   WindowedFrameDataGenerator>;

DataGenerator create_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const DataSpecification& specification);
void compute_generator(DataGenerator& generator);

#endif
