#ifndef __RANDOMPATHS_CLASS__
#define __RANDOMPATHS_CLASS__

#include <vector>
#include <glm/glm.hpp>

#include "../../misc/PerlinNoise.hpp"

class Movable;

class RandomPaths {
	public:
		void apply_force(std::vector<Movable>& movables);
	private:
		glm::vec3 generate_target(const Movable& movable, unsigned int group_id);

		PerlinNoise _perlin_noise;
};

#endif
