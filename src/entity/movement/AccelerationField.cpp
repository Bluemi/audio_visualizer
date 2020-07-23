#include "AccelerationField.hpp"

#include "../Movable.hpp"

AccelerationField::AccelerationField()
	: _perlin_noise(3), _time(0), _force(0.004f)
{}

void AccelerationField::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables) {
		apply_force(&m);
	}
}

const float NOISE_OFFSET = 2000.7f;
const float NOISE_SCALE = 0.2f;

void AccelerationField::apply_force(Movable* movable) {
	float fx = _perlin_noise({movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*1 + _time,
							  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*1 + _time});

	float fy = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET*2 + _time,
							  movable->get_position().z*NOISE_SCALE + NOISE_OFFSET*2 + _time});

	float fz = _perlin_noise({movable->get_position().x*NOISE_SCALE + NOISE_OFFSET*3 + _time,
							  movable->get_position().y*NOISE_SCALE + NOISE_OFFSET*3 + _time});

	movable->update_acceleration(glm::vec3(fx, fy, fz)*_force);
}

float AccelerationField::get_force() const {
	return _force;
}

void AccelerationField::update_time(float time) {
	_time += time;
}

void AccelerationField::set_force(float force) {
	_force = force;
}
