#ifndef __EVENT_CLASS__
#define __EVENT_CLASS__

#include <variant>
#include <vector>

#include "TickEvent.hpp"
#include "BeatEvent.hpp"
#include "ArousalEvent.hpp"
#include "ValenceEvent.hpp"

using _EventVar = std::variant<TickEvent, BeatEvent, ArousalEvent, ValenceEvent>;

class Event
{
	public:
		template<typename Ev>
		Event(const Ev& event, double time) : _event(event), _time(time) {}

		double get_time() const { return _time; }
		_EventVar get_event() const { return _event; }
		bool operator<(const Event& e)
		{
			return _time < e._time;
		}
	private:
		_EventVar _event;
		double _time;
};

using EventList = std::vector<Event>;

#endif
