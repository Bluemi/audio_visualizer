#include "GroupMovement.hpp"

#include <iostream>

GroupMovement::GroupMovement(const _GroupMovementVar& movement)
	: _group_movement(movement)
{}

void GroupMovement::with_groups(const std::vector<std::string>& groups) {
	_groups.insert(_groups.end(), groups.cbegin(), groups.cend());
}

void GroupMovement::apply_to(EntityBuffer* entity_buffer) {
	std::visit([this, &entity_buffer](auto& m) { apply_group_movement_to(entity_buffer, m, this->_groups); }, _group_movement);
}
