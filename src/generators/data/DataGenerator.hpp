#ifndef __DATAGENERATOR_CLASS__
#define __DATAGENERATOR_CLASS__

#include <variant>

#include <essentia/pool.h>

#include "../../data/DataSpecification.hpp"
#include "AudioDataGenerator.hpp"
#include "FrameDataGenerator.hpp"
#include "WindowedFrameDataGenerator.hpp"
#include "SpectrumDataGenerator.hpp"
#include "BarkBandsDataGenerator.hpp"
#include "BarkBandsDifferenceDataGenerator.hpp"
#include "SpectrumPeakDataGenerator.hpp"
#include "PitchClassProfileDataGenerator.hpp"
#include "ChordDataGenerator.hpp"
#include "ArousalDataGenerator.hpp"
#include "ValenceDataGenerator.hpp"
#include "TickDataGenerator.hpp"
#include "WriteDataGenerator.hpp"

using DataGenerator = std::variant<AudioDataGenerator,
								   FrameDataGenerator,
								   WindowedFrameDataGenerator,
								   SpectrumDataGenerator,
								   BarkBandsDataGenerator,
								   BarkBandsDifferenceDataGenerator,
								   SpectrumPeakDataGenerator,
								   PitchClassProfileDataGenerator,
								   ChordDataGenerator,
								   ArousalDataGenerator,
								   ValenceDataGenerator,
	  							   TickDataGenerator,
								   WriteDataGenerator>;

DataGenerator create_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const DataSpecification& specification);
void compute_generator(DataGenerator& generator);

#endif
