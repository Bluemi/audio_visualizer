#include "Accelerator.hpp"

Accelerator::Accelerator()
	: velocity(0.f), acceleration(0.f)
{}

void Accelerator::tick() {
	velocity += acceleration;
	acceleration = glm::vec3(0.f, 0.f, 0.f);
}
