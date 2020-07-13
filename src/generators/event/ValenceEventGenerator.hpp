#ifndef __VALENCEEVENTGENERATOR_CLASS__
#define __VALENCEEVENTGENERATOR_CLASS__

#include <essentia/pool.h>

#include "../../event/Event.hpp"

class ValenceEventGenerator {
	public:
		EventList compute(const essentia::Pool& pool) const;
};

#endif
