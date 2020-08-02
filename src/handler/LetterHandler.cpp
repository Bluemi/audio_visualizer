#include "LetterHandler.hpp"

#include <iostream>

#include "entity/movement/GroupMovement.hpp"

LetterHandler::LetterHandler(char letter) : _letter_movement(letter) {}

void LetterHandler::update(const essentia::Pool& pool) {
	GroupMovement::apply_group_movement_to(entity_buffer, _letter_movement, groups);
}
