#include "DragHandler.hpp"

#include "entity/movement/GroupMovement.hpp"

DragHandler::DragHandler(float intensity)
	: _velocity_drag(intensity), _color_drag(intensity)
{}

void DragHandler::update(const essentia::Pool&) {
	GroupMovement::apply_group_movement_to(entity_buffer, _velocity_drag, groups);
	GroupMovement::apply_group_movement_to(entity_buffer, _color_drag, groups);
}
