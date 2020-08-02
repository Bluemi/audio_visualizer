#include "LetterHandler.hpp"

#include <iostream>

#include "entity/movement/GroupMovement.hpp"

LetterHandler::LetterHandler() : _letter_movement('B') {}

void LetterHandler::update(const essentia::Pool& pool) {
	GroupMovement::apply_group_movement_to(entity_buffer, _letter_movement, groups);
}
