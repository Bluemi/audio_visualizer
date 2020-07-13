#ifndef __INFORMATIONCONTAINER_CLASS__
#define __INFORMATIONCONTAINER_CLASS__

#include <essentia/pool.h>

#include "../event/Event.hpp"

class InformationContainer {
	public:
		InformationContainer(const EventList& event_list, const essentia::Pool& pool);

		const EventList& get_event_list() const;
		const essentia::Pool& get_pool() const;
	private:
		EventList _event_list;
		essentia::Pool _pool;
};

#endif
