#ifndef __EVENTGENERATOR_CLASS__
#define __EVENTGENERATOR_CLASS__

#include <variant>

#include "TickEventGenerator.hpp"
#include "BeatEventGenerator.hpp"
#include "ArousalEventGenerator.hpp"
#include "../../event/EventSpecification.hpp"

using EventGenerator = std::variant<TickEventGenerator, BeatEventGenerator, ArousalEventGenerator>;

EventGenerator create_event_generator(const EventSpecification& event_specification);
EventList compute_event_generator(const EventGenerator& generator, const essentia::Pool& pool);

#endif
