#include "BeatEventGenerator.hpp"

#include <essentia/pool.h>

EventList BeatEventGenerator::compute(const essentia::Pool& pool) const
{
	EventList event_list;
	std::vector<essentia::Real> ticks =  pool.value<std::vector<essentia::Real>>("highlevel.tick_positions");
	for (const auto& i : ticks)
	{
		Event e(BeatEvent(1.f), i-0.01f);
		event_list.push_back(e);
	}

	return event_list;
}
