#include "VelocityDrag.hpp"

#include "../Movable.hpp"

VelocityDrag::VelocityDrag(float intensity)
	: _intensity(intensity)
{}

void VelocityDrag::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables) {
		apply_force(&m);
	}
}

void VelocityDrag::apply_force(Movable* movable) {
	movable->update_acceleration(movable->get_velocity() * -_intensity);
}
