#include "ValenceEventGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

EventList ValenceEventGenerator::compute(const essentia::Pool& pool) const
{
	std::cout << "Creating Valence Events... " << std::flush;
	EventList event_list;

	std::vector<float> valence_timeline = pool.value<std::vector<float>>(data_identifier::VALENCE_TIMELINE);

	for (unsigned int i = 0; i < valence_timeline.size(); i++)
	{
		Event event(ValenceEvent(valence_timeline[i]), i*(static_cast<float>(1024) / static_cast<float>(44100)));
		event_list.push_back(event);
	}

	std::cout << "Done." << std::endl;

	return event_list;
}
