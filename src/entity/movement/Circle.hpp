#ifndef __CIRCLE_CLASS__
#define __CIRCLE_CLASS__

#include <vector>

#include <glm/glm.hpp>

class Movable;

class Circle {
	public:
		Circle();
		Circle(const glm::vec3& center, float radius);

		void apply_force(std::vector<Movable>& movables);
		void apply_force(Movable* movable);
	private:
		glm::vec3 _center;
		float _radius;
};

#endif
