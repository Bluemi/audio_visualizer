#include "TickEventGenerator.hpp"

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"

EventList TickEventGenerator::compute(const essentia::Pool& pool) const
{
	std::cout << "Generating TickEvents... " << std::flush;
	EventList event_list;
	std::vector<essentia::Real> ticks =  pool.value<std::vector<essentia::Real>>(data_identifier::TICK_POSITIONS);
	for (const auto& i : ticks)
	{
		Event e(TickEvent(), i-0.01f);
		event_list.push_back(e);
	}

	std::cout << "Done." << std::endl;

	return event_list;
}
