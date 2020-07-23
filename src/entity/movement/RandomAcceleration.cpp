#include "RandomAcceleration.hpp"

#include <cstdlib>
#include <glm/glm.hpp>

#include "../Movable.hpp"

RandomAcceleration::RandomAcceleration(float intensity)
	: _intensity(intensity), _should_be_removed(false)
{}

float get_rand(float intensity) {
	return ((std::rand() % 101) - 50) / 50.f * intensity;
}

void RandomAcceleration::apply_force(Movable* movable) {
	if (!_should_be_removed) {
		glm::vec3 force = glm::vec3(get_rand(_intensity), get_rand(_intensity), get_rand(_intensity));
		movable->update_acceleration(force);
	}
	_should_be_removed = true;
}

bool RandomAcceleration::should_be_removed() const {
	return _should_be_removed;
}
