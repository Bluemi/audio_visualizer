#ifndef __TICKEVENTGENERATOR_CLASS__
#define __TICKEVENTGENERATOR_CLASS__

#include "../../event/Event.hpp"

namespace essentia {
	class Pool;
}

class TickEventGenerator {
	public:
		EventList compute(const essentia::Pool& pool) const;
};

#endif
