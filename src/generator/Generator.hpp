#ifndef __GENERATOR_CLASS__
#define __GENERATOR_CLASS__

#include <variant>

#include <essentia/pool.h>

#include "../event/EventSpecification.hpp"
#include "BeatDataGenerator.hpp"
#include "AudioDataGenerator.hpp"

using Generator = std::variant<AudioDataGenerator, BeatDataGenerator>;

Generator build_generator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const EventSpecification& specification);
void compute_generator(Generator& generator);

#endif
