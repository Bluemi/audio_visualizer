#include "RandomAccelerationHandler.hpp"

#include "../entity/EntityIterator.hpp"

RandomAccelerationHandler::RandomAccelerationHandler(float strength)
	: _strength(strength), _random_distribution(-strength, strength)
{}

void RandomAccelerationHandler::update(const essentia::Pool& pool) {
	for (Movable& movable : EntityIterator::iter(entity_buffer)) {
		glm::vec3 force = glm::vec3(_random_distribution(_random_generator), _random_distribution(_random_generator), _random_distribution(_random_generator));
		movable.update_acceleration(force);
	}
}
