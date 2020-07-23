#include "SeekTargets.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include "../Movable.hpp"

const float SWITCH_DIFF = 0.2f;
const float MAX_MAGNITUDE = 0.01f;

SeekTargets::SeekTargets(const std::vector<Movable>& targets)
	: _targets(targets), target_index(0)
{}

void SeekTargets::apply_force(Movable* movable) {
	glm::vec3 target = _targets[target_index].get_position();
	glm::vec3 dir = target - movable->get_position();
	glm::vec3 update = dir - movable->get_velocity();
	if (glm::length(update) > MAX_MAGNITUDE) {
		update *= MAX_MAGNITUDE / glm::length(update);
	}

	movable->update_acceleration(update);

	if (glm::length(dir) < SWITCH_DIFF) {
		target_index = (target_index + 1) % _targets.size();
	}
}
