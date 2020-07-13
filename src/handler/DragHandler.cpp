#include "DragHandler.hpp"

DragHandler::DragHandler(float intensity)
	: _velocity_drag(intensity), _color_drag(intensity)
{}

void DragHandler::update(const essentia::Pool&) {
	visualizer::GroupMovement::apply_group_movement_to(&(_visualizer->get_entities()), _velocity_drag, _groups);
	visualizer::GroupMovement::apply_group_movement_to(&(_visualizer->get_entities()), _color_drag, _groups);
}
