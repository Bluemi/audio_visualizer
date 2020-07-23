#ifndef __COLORTARGET_CLASS__
#define __COLORTARGET_CLASS__

#include <glm/glm.hpp>

#include "IMovement.hpp"

class ColorTarget : public IMovementCloneable<ColorTarget> {
	public:
		ColorTarget(const glm::vec3& target, float strength);
		virtual void apply_force(Movable* movable) override;
		virtual bool should_be_removed() const override;
	private:
		glm::vec3 _target;
		float _strength;
		bool _used;
};

#endif
