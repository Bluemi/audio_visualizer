#ifndef __IMAGE_EVENT_GENERATOR_CLASS__
#define __IMAGE_EVENT_GENERATOR_CLASS__

#include "../../event/Event.hpp"

namespace essentia {
	class Pool;
}

class ImageEventGenerator {
	public:
		ImageEventGenerator(int image_id, float start_time, float end_time);
		EventList compute(const essentia::Pool& pool) const;
	private:
		int _image_id;
		float _start_time;
		float _end_time;
};

#endif
