#ifndef __QUERYSPACE_CLASS__
#define __QUERYSPACE_CLASS__

#include <glm/glm.hpp>

class Movable;

/**
 * Defines a Cube Space around _center with side length = 2*size.
 * If not _set all movables are considered as inside the space.
 */
class QuerySpace {
	public:
		QuerySpace();
		QuerySpace(const glm::vec3& center, const glm::vec3& size);

		bool is_position_included(const glm::vec3& position) const;
	private:
		glm::vec3 _center;
		glm::vec3 _size;
		bool _set;
};

#endif
