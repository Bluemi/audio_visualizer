#ifndef __STDCOLOR_CLASS__
#define __STDCOLOR_CLASS__

#include <glm/glm.hpp>

#include "IMovement.hpp"

class StdColor : public IMovementCloneable<StdColor> {
	public:
		StdColor(float strength);
		virtual void init(Movable* movable) override;
		virtual void apply_force(Movable* movable) override;
	private:
		float _strength;
		glm::vec3 _color;
};

#endif
