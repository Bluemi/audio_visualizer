#ifndef __DRAGHANDLER_CLASS__
#define __DRAGHANDLER_CLASS__

#include "entity/movement/VelocityDrag.hpp"
#include "entity/movement/ColorDrag.hpp"

#include "BaseHandler.hpp"

class DragHandler : public BaseHandler {
	public:
		DragHandler(float intensity);
		void update(const essentia::Pool&);
	private:
		VelocityDrag _velocity_drag;
		ColorDrag _color_drag;
};

#endif
