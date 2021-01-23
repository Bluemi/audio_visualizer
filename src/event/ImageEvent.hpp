#ifndef __IMAGE_EVENT_CLASS__
#define __IMAGE_EVENT_CLASS__

#include <string>

class ImageEvent {
	public:
		ImageEvent(int image_id) : image_id(image_id) {}
		int image_id;
};

#endif
