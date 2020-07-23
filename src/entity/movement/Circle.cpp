#include "Circle.hpp"

#include <iostream>

#include "../Movable.hpp"

const float MAX_MAGNITUDE = 0.03f;

Circle::Circle()
	: _radius(1.f)
{}

Circle::Circle(const glm::vec3& center, float radius)
	: _center(center), _radius(radius)
{}

void Circle::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables) {
		apply_force(&m);
	}
}

void Circle::apply_force(Movable* movable) {
	glm::vec3 center_to_pos = movable->get_position() - _center;
	if (glm::length(center_to_pos) < 0.0001f) {
		movable->update_acceleration(glm::vec3(MAX_MAGNITUDE, 0.f, 0.f));
	}
	else {
		glm::vec3 norm_point = glm::normalize(glm::vec3(center_to_pos.x, 0.f, center_to_pos.z));
		glm::vec3 perpendicular_direction = glm::cross(norm_point, glm::vec3(0.f, 1.f, 0.f));
		glm::vec3 p = norm_point + perpendicular_direction;
		glm::vec3 target_point = _center + glm::normalize(p) * _radius;

		glm::vec3 dir = target_point - movable->get_position();
		glm::vec3 update = dir - movable->get_velocity();

		if (glm::length(update) > MAX_MAGNITUDE) {
			update *= MAX_MAGNITUDE / glm::length(update);
		}

		movable->update_acceleration(update);
	}
}
