#include "SimpleDrag.hpp"

#include <glm/glm.hpp>

#include "../Movable.hpp"

SimpleDrag::SimpleDrag(float drag)
	: _drag(drag)
{}

void SimpleDrag::apply_force(Movable* movable) {
	glm::vec3 velocity = movable->get_velocity();
	movable->update_acceleration(velocity * -_drag);
}
