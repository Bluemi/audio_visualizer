#ifndef __DATAGENERATOR_CLASS__
#define __DATAGENERATOR_CLASS__

#include <variant>

#include <essentia/pool.h>

#include "../../data/DataSpecification.hpp"
#include "BeatDataGenerator.hpp"
#include "AudioDataGenerator.hpp"
#include "WriteDataGenerator.hpp"

using DataGenerator = std::variant<AudioDataGenerator, BeatDataGenerator, WriteDataGenerator>;

DataGenerator create_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const DataSpecification& specification);
void compute_generator(DataGenerator& generator);

#endif
