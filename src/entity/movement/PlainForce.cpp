#include "PlainForce.hpp"

#include "../Movable.hpp"

PlainForce::PlainForce(float strength)
	: _strength(strength)
{}

void PlainForce::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables)
		m.update_acceleration(glm::vec3(0.f, m.get_position().y * -_strength, 0.f));
}

void PlainForce::set_strength(float strength) {
	_strength = strength;
}
