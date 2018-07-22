#include "TickEventGenerator.hpp"

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"

EventList TickEventGenerator::compute(const essentia::Pool& pool) const
{
	EventList event_list;
	std::vector<essentia::Real> ticks =  pool.value<std::vector<essentia::Real>>(data_identifier::TICK_POSITIONS);
	for (const auto& i : ticks)
	{
		Event e(TickEvent(1.f), i-0.01f);
		event_list.push_back(e);
	}

	return event_list;
}
