#ifndef __BASEHANDLER_CLASS__
#define __BASEHANDLER_CLASS__

namespace essentia { class Pool; }

#include "entity/EntityBuffer.hpp"

class BaseHandler {
	public:
		template<typename EventType>
		void operator()(const EventType&) {}
		void update(const essentia::Pool&) {}

		EntityBuffer* entity_buffer;
		unsigned int frame_counter;
		std::vector<std::string> groups;
};

#define USE_BASE_OP using BaseHandler::operator();

#endif
