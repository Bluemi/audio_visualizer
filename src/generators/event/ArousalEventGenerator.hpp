#ifndef __AROUSALEVENTGENERATOR_CLASS__
#define __AROUSALEVENTGENERATOR_CLASS__

#include <essentia/pool.h>

#include "../../event/Event.hpp"

class ArousalEventGenerator {
	public:
		EventList compute(const essentia::Pool& pool) const;
};

#endif
