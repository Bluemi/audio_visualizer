#ifndef __GROUPMOVEMENT_CLASS__
#define __GROUPMOVEMENT_CLASS__

#include <vector>
#include <string>

#include "../EntityBuffer.hpp"
#include "Circle.hpp"
#include "AccelerationField.hpp"
#include "VelocityDrag.hpp"
#include "ColorDrag.hpp"
#include "PlainForce.hpp"
#include "RandomPaths.hpp"
#include "LetterMovement.hpp"

using _GroupMovementVar = std::variant<
	Circle,
	AccelerationField,
	VelocityDrag,
	ColorDrag,
	PlainForce,
	RandomPaths,
	LetterMovement
>;

class GroupMovement {
	public:
		GroupMovement(const _GroupMovementVar& movement);
		void with_groups(const std::vector<std::string>& groups);

		void apply_to(EntityBuffer* entity_buffer);

		template<typename GroupMovementType>
		static void apply_group_movement_to(EntityBuffer* entity_buffer, GroupMovementType& movement, const std::vector<std::string>& groups) {
			if (groups.empty()) {
				for (auto iter = entity_buffer->begin(); iter != entity_buffer->end(); ++iter) {
					std::vector<Movable>& movables = iter->second;
					movement.apply_force(movables);
				}
			} else {
				for (const std::string& group : groups) {
					std::vector<Movable>& movables = entity_buffer->at(group);
					movement.apply_force(movables);
				}
			}
		}
	protected:
		std::vector<std::string> _groups;
		_GroupMovementVar _group_movement;
};

#endif
