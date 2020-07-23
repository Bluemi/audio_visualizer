#ifndef __ACCELERATOR_CLASS__
#define __ACCELERATOR_CLASS__

#include <glm/glm.hpp>

class Accelerator {
	public:
		Accelerator();

		void tick();

		glm::vec3 velocity;
		glm::vec3 acceleration;
};

#endif
