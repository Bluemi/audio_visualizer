#include "SimpleColorDrag.hpp"

#include "../Movable.hpp"

SimpleColorDrag::SimpleColorDrag(float drag)
	: _drag(drag)
{}

void SimpleColorDrag::apply_force(Movable* movable) {
	glm::vec3 dir = movable->get_color_velocity();
	movable->update_color_velocity(dir * -_drag);
}
