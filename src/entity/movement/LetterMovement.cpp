#include "LetterMovement.hpp"

#include "../Movable.hpp"

#include <glm/gtx/norm.hpp>

constexpr float MAX_MAGNITUDE = 0.007f;

LetterMovement::LetterMovement(char letter) {
	init_points(letter);
}

void LetterMovement::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables) {
		apply_force(&m);
	}
}

void LetterMovement::apply_force(Movable* movable) {
	glm::vec3 target_point = _points[0];
	for (const glm::vec3& point : _points) {
		if (glm::distance2(point, movable->get_position()) < glm::distance2(target_point, movable->get_position())) {
			target_point = point;
		}
	}

	glm::vec3 dir = target_point - movable->get_position();
	glm::vec3 update = dir - movable->get_velocity();

	if (glm::length(update) > MAX_MAGNITUDE) {
		update *= MAX_MAGNITUDE / glm::length(update);
	}

	movable->update_acceleration(update);
}

// TODO: make dependent on letter
void LetterMovement::init_points(char letter) {
	_points.push_back(glm::vec3(0.f, 0.f, 0.f)); // 0
	_points.push_back(glm::vec3(0.f, 0.5f, 0.25f)); // 1
	_points.push_back(glm::vec3(0.f, 1.f, 0.5f)); // 2
	_points.push_back(glm::vec3(0.f, 1.5f, 0.75f)); // 3
	_points.push_back(glm::vec3(0.f, 2.f, 1.f)); // 4
	_points.push_back(glm::vec3(0.f, 1.f, 1.f)); // 5
	_points.push_back(glm::vec3(0.f, 1.5f, 1.25f)); // 6
	_points.push_back(glm::vec3(0.f, 1.f, 1.5f)); // 7
	_points.push_back(glm::vec3(0.f, 0.5f, 1.75f)); // 8
	_points.push_back(glm::vec3(0.f, 0.f, 2.f)); // 9
}
