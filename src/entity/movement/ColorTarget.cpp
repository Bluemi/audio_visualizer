#include "ColorTarget.hpp"

#include "../Movable.hpp"

ColorTarget::ColorTarget(const glm::vec3& target, float strength)
	: _target(target), _strength(strength), _used(false)
{}

void ColorTarget::apply_force(Movable* movable) {
	if (!_used) {
		glm::vec3 direction = (_target - movable->get_color()) * _strength;
		movable->update_color_acceleration(direction);
		_used = true;
	}
}

bool ColorTarget::should_be_removed() const {
	return _used;
}
