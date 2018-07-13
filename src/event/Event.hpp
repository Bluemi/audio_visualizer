#ifndef __EVENT_CLASS__
#define __EVENT_CLASS__

#include <variant>
#include <vector>

#include "BeatEvent.hpp"

using _EventVar = std::variant<BeatEvent>;

class Event
{
	public:
		template<typename Ev>
		Event(const Ev& event, double time) : _event(event), _time(time) {}

		double get_time() const { return _time; }
	private:
		_EventVar _event;
		double _time;
};

using EventList = std::vector<Event>;

#endif
