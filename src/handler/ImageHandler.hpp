#ifndef __IMAGE_HANDLER_CLASS__
#define __IMAGE_HANDLER_CLASS__

#include <random>

#include "BaseHandler.hpp"

class ImageEvent;

class ImageHandler : public BaseHandler {
	public:
		ImageHandler(const std::vector<std::string>& image_paths);
		void init(visualizer::ShapeHeap& shape_heap);
		void update(const essentia::Pool& pool);
		void operator()(const ImageEvent& image_event);
		USE_BASE_OP;
	private:
		void apply_force(Movable* movable);

		std::vector<std::string> _image_paths;
		int _current_image;
		std::vector<std::vector<glm::vec3>> _images;
};

#endif
