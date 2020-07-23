#ifndef __ACCELERATIONFIELD_CLASS__
#define __ACCELERATIONFIELD_CLASS__

#include <vector>

#include "../../misc/PerlinNoise.hpp"

class Movable;

class AccelerationField {
	public:
		AccelerationField();

		void apply_force(std::vector<Movable>& movables);
		void apply_force(Movable* movable);

		float get_force() const;

		void update_time(float time);
		void set_force(float force);
	private:
		PerlinNoise _perlin_noise;
		float _time;
		float _force;
};

#endif
