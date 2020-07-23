#include "QuerySpace.hpp"

#include "../../misc/Misc.hpp"
#include "../Movable.hpp"

QuerySpace::QuerySpace()
	: _set(false), _center(0.f, 0.f, 0.f), _size(0.f, 0.f, 0.f)
{}

QuerySpace::QuerySpace(const glm::vec3& center, const glm::vec3& size)
	: _center(center), _size(size), _set(true)
{}

bool QuerySpace::is_position_included(const glm::vec3& position) const {
	if (!_set) { return true; }
	return math::is_included(position, _center, _size);
}
