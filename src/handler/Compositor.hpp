#ifndef __COMPOSITOR_CLASS__
#define __COMPOSITOR_CLASS__

#include "../information/InformationContainer.hpp"
#include "Handler.hpp"

/**
 * Tasks:
 * - creating groups of entities
 * - creating/manipulating handlers
 */
class Compositor {
	public:
		void update(visualizer::EntityBuffer* entity_buffer, HandlerList& handler_list, const InformationContainer& information_container, const EventList& current_events, unsigned int frame_counter);
};

#endif
