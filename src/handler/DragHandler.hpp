#ifndef __DRAGHANDLER_CLASS__
#define __DRAGHANDLER_CLASS__

#include <visualizer/entity/movement/VelocityDrag.hpp>
#include <visualizer/entity/movement/ColorDrag.hpp>

#include "BaseHandler.hpp"

class DragHandler : public BaseHandler {
	public:
		DragHandler(float intensity);
		void update(const essentia::Pool&);
	private:
		visualizer::VelocityDrag _velocity_drag;
		visualizer::ColorDrag _color_drag;
};

#endif
