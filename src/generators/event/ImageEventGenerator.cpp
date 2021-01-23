#include "ImageEventGenerator.hpp"

#include <algorithm>

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"
#include "../../misc/Misc.hpp"


ImageEventGenerator::ImageEventGenerator(int image_id, float start_time, float end_time) : _image_id(image_id), _start_time(start_time), _end_time(end_time) {}

EventList ImageEventGenerator::compute(const essentia::Pool& pool) const {
	std::cout << "Generating ImageEvents... " << std::flush;

	EventList event_list;
	event_list.push_back(Event(ImageEvent(_image_id), _start_time));
	event_list.push_back(Event(ImageEvent(-1), _end_time));
	std::cout << "Done." << std::endl;
	return event_list;
}
