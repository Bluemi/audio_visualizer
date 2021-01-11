#include "TextEventGenerator.hpp"

#include <algorithm>

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"
#include "../../misc/Misc.hpp"


TextEventGenerator::TextEventGenerator(const std::vector<std::tuple<float, std::string>>& texts) : _texts(texts) {}

EventList TextEventGenerator::compute(const essentia::Pool& pool) const {
	std::cout << "Generating TextEvents... " << std::flush;

	EventList event_list;
	for (auto ev : _texts) {
		Event e(TextEvent(std::get<1>(ev)), std::get<0>(ev));
		event_list.push_back(e);
	}
	std::cout << "Done." << std::endl;
	return event_list;
}
