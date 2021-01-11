#ifndef __TEXT_EVENT_GENERATOR_CLASS__
#define __TEXT_EVENT_GENERATOR_CLASS__

#include "../../event/Event.hpp"

namespace essentia {
	class Pool;
}

class TextEventGenerator {
	public:
		TextEventGenerator(const std::vector<std::tuple<float, std::string, bool>>& texts);
		EventList compute(const essentia::Pool& pool) const;
	private:
		std::vector<std::tuple<float, std::string, bool>> _texts;
};

#endif
