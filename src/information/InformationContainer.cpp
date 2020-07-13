#include "InformationContainer.hpp"

InformationContainer::InformationContainer(const EventList& event_list, const essentia::Pool& pool)
	: _event_list(event_list), _pool(pool)
{}

const EventList& InformationContainer::get_event_list() const {
	return _event_list;
}

const essentia::Pool& InformationContainer::get_pool() const {
	return _pool;
}
