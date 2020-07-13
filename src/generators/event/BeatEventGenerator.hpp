#ifndef __BEATEVENTGENERATOR_CLASS__
#define __BEATEVENTGENERATOR_CLASS__

#include "../../event/Event.hpp"

namespace essentia {
	class Pool;
}

class BeatEventGenerator {
	public:
		EventList compute(const essentia::Pool& pool) const;
};

#endif
