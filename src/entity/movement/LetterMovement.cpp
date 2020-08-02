#include "LetterMovement.hpp"

#include "../Movable.hpp"

#include <glm/gtx/norm.hpp>

constexpr float MAX_MAGNITUDE = 0.01f;

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
	if (letter == 'A') {
		_points.push_back(glm::vec3(0.f, 1.0f, 0.48f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.98f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.98f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.96f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.96f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.94f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.94f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.92f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.92f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.9f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.9f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.88f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.88f, 0.56f));
		_points.push_back(glm::vec3(0.f, 0.86f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.86f, 0.56f));
		_points.push_back(glm::vec3(0.f, 0.84f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.84f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.8200000000000001f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.8200000000000001f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.8f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.8f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.78f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.78f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.76f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.76f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.74f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.74f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.72f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.72f, 0.64f));
		_points.push_back(glm::vec3(0.f, 0.7f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.7f, 0.64f));
		_points.push_back(glm::vec3(0.f, 0.6799999999999999f, 0.32f));
		_points.push_back(glm::vec3(0.f, 0.6799999999999999f, 0.66f));
		_points.push_back(glm::vec3(0.f, 0.6599999999999999f, 0.32f));
		_points.push_back(glm::vec3(0.f, 0.6599999999999999f, 0.66f));
		_points.push_back(glm::vec3(0.f, 0.64f, 0.3f));
		_points.push_back(glm::vec3(0.f, 0.64f, 0.68f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.3f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.68f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.28f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.7f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.28f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.7f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.26f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.72f));
		_points.push_back(glm::vec3(0.f, 0.54f, 0.26f));
		_points.push_back(glm::vec3(0.f, 0.54f, 0.72f));
		_points.push_back(glm::vec3(0.f, 0.52f, 0.24f));
		_points.push_back(glm::vec3(0.f, 0.52f, 0.74f));
		_points.push_back(glm::vec3(0.f, 0.5f, 0.24f));
		_points.push_back(glm::vec3(0.f, 0.5f, 0.74f));
		_points.push_back(glm::vec3(0.f, 0.48f, 0.22f));
		_points.push_back(glm::vec3(0.f, 0.48f, 0.76f));
		_points.push_back(glm::vec3(0.f, 0.45999999999999996f, 0.22f));
		_points.push_back(glm::vec3(0.f, 0.45999999999999996f, 0.76f));
		_points.push_back(glm::vec3(0.f, 0.43999999999999995f, 0.2f));
		_points.push_back(glm::vec3(0.f, 0.43999999999999995f, 0.78f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.2f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.22f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.24f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.26f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.28f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.3f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.32f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.56f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.64f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.66f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.68f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.7f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.72f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.74f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.76f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.78f));
		_points.push_back(glm::vec3(0.f, 0.4f, 0.18f));
		_points.push_back(glm::vec3(0.f, 0.4f, 0.8f));
		_points.push_back(glm::vec3(0.f, 0.38f, 0.18f));
		_points.push_back(glm::vec3(0.f, 0.38f, 0.8f));
		_points.push_back(glm::vec3(0.f, 0.36f, 0.16f));
		_points.push_back(glm::vec3(0.f, 0.36f, 0.82f));
		_points.push_back(glm::vec3(0.f, 0.33999999999999997f, 0.16f));
		_points.push_back(glm::vec3(0.f, 0.33999999999999997f, 0.82f));
		_points.push_back(glm::vec3(0.f, 0.31999999999999995f, 0.14f));
		_points.push_back(glm::vec3(0.f, 0.31999999999999995f, 0.84f));
		_points.push_back(glm::vec3(0.f, 0.30000000000000004f, 0.14f));
		_points.push_back(glm::vec3(0.f, 0.30000000000000004f, 0.84f));
		_points.push_back(glm::vec3(0.f, 0.28f, 0.12f));
		_points.push_back(glm::vec3(0.f, 0.28f, 0.86f));
		_points.push_back(glm::vec3(0.f, 0.26f, 0.12f));
		_points.push_back(glm::vec3(0.f, 0.26f, 0.86f));
		_points.push_back(glm::vec3(0.f, 0.24f, 0.1f));
		_points.push_back(glm::vec3(0.f, 0.24f, 0.88f));
		_points.push_back(glm::vec3(0.f, 0.21999999999999997f, 0.1f));
		_points.push_back(glm::vec3(0.f, 0.21999999999999997f, 0.88f));
		_points.push_back(glm::vec3(0.f, 0.19999999999999996f, 0.08f));
		_points.push_back(glm::vec3(0.f, 0.19999999999999996f, 0.9f));
		_points.push_back(glm::vec3(0.f, 0.18000000000000005f, 0.08f));
		_points.push_back(glm::vec3(0.f, 0.18000000000000005f, 0.9f));
		_points.push_back(glm::vec3(0.f, 0.16000000000000003f, 0.06f));
		_points.push_back(glm::vec3(0.f, 0.16000000000000003f, 0.92f));
		_points.push_back(glm::vec3(0.f, 0.14f, 0.06f));
		_points.push_back(glm::vec3(0.f, 0.14f, 0.92f));
		_points.push_back(glm::vec3(0.f, 0.12f, 0.04f));
		_points.push_back(glm::vec3(0.f, 0.12f, 0.94f));
		_points.push_back(glm::vec3(0.f, 0.09999999999999998f, 0.04f));
		_points.push_back(glm::vec3(0.f, 0.09999999999999998f, 0.94f));
		_points.push_back(glm::vec3(0.f, 0.07999999999999996f, 0.02f));
		_points.push_back(glm::vec3(0.f, 0.07999999999999996f, 0.96f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.02f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.96f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.98f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.98f));
	} else if (letter == 'B') {
		_points.push_back(glm::vec3(0.f, 1.0f, 0.f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.02f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.04f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.06f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.08f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.1f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.12f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.14f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.16f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.18f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.2f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.22f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.24f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.26f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.28f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.3f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.32f));
		_points.push_back(glm::vec3(0.f, 1.0f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.98f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.98f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.98f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.96f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.96f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.96f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.94f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.94f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.94f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.92f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.92f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.9f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.9f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.88f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.88f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.86f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.86f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.84f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.84f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.8200000000000001f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.8200000000000001f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.8f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.8f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.78f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.78f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.76f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.76f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.74f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.74f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.72f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.72f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.7f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.7f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.6799999999999999f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.6799999999999999f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.6599999999999999f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.6599999999999999f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.64f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.64f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.64f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.62f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.02f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.04f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.06f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.08f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.1f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.12f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.14f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.16f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.18f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.2f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.22f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.24f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.26f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.28f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.3f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.32f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.6f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.5800000000000001f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.56f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.54f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.54f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.52f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.52f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.52f, 0.56f));
		_points.push_back(glm::vec3(0.f, 0.5f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.5f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.48f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.48f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.45999999999999996f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.45999999999999996f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.43999999999999995f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.43999999999999995f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.42000000000000004f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.4f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.4f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.38f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.38f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.36f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.36f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.33999999999999997f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.33999999999999997f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.31999999999999995f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.31999999999999995f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.30000000000000004f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.30000000000000004f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.28f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.28f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.26f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.26f, 0.62f));
		_points.push_back(glm::vec3(0.f, 0.24f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.24f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.21999999999999997f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.21999999999999997f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.19999999999999996f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.19999999999999996f, 0.6f));
		_points.push_back(glm::vec3(0.f, 0.18000000000000005f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.18000000000000005f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.16000000000000003f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.16000000000000003f, 0.58f));
		_points.push_back(glm::vec3(0.f, 0.14f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.14f, 0.56f));
		_points.push_back(glm::vec3(0.f, 0.12f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.12f, 0.52f));
		_points.push_back(glm::vec3(0.f, 0.12f, 0.54f));
		_points.push_back(glm::vec3(0.f, 0.09999999999999998f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.09999999999999998f, 0.5f));
		_points.push_back(glm::vec3(0.f, 0.07999999999999996f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.07999999999999996f, 0.46f));
		_points.push_back(glm::vec3(0.f, 0.07999999999999996f, 0.48f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.4f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.42f));
		_points.push_back(glm::vec3(0.f, 0.06000000000000005f, 0.44f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.32f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.34f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.36f));
		_points.push_back(glm::vec3(0.f, 0.040000000000000036f, 0.38f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.02f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.04f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.06f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.08f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.1f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.12f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.14f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.16f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.18f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.2f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.22f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.24f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.26f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.28f));
		_points.push_back(glm::vec3(0.f, 0.020000000000000018f, 0.3f));
	}
}
