#include "SetSpeed.hpp"

#include "../Movable.hpp"

SetSpeed::SetSpeed(float x, float y, float z)
	: _x(x), _y(y), _z(z), _should_be_removed(false)
{}

void SetSpeed::apply_force(Movable* movable) {
	if (!_should_be_removed) {
		movable->set_velocity(glm::vec3(_x, _y, _z));
	}
	_should_be_removed = true;
}

bool SetSpeed::should_be_removed() const {
	return _should_be_removed;
}
