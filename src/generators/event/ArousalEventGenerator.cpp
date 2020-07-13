#include "ArousalEventGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

EventList ArousalEventGenerator::compute(const essentia::Pool& pool) const {
	std::cout << "Creating Arousal Events... " << std::flush;

	EventList event_list;
	std::vector<float> arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);

	for (unsigned int i = 0; i < arousal_timeline.size(); i++) {
		Event e(ArousalEvent(arousal_timeline[i]), i*(1024.0/44100.0));
		event_list.push_back(e);
	}

	std::cout << "Done." << std::endl;

	return event_list;
}
