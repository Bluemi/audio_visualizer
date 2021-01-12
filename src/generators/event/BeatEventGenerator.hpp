#ifndef __BEATEVENTGENERATOR_CLASS__
#define __BEATEVENTGENERATOR_CLASS__

#include "../../event/Event.hpp"

namespace essentia {
	class Pool;
}

class BeatEventGenerator {
	public:
		BeatEventGenerator(const std::vector<std::tuple<float, float>>& accelerations) : _accelerations(accelerations) {}
		EventList compute(const essentia::Pool& pool) const;
		std::vector<std::tuple<float, float>> _accelerations;
};

#endif
