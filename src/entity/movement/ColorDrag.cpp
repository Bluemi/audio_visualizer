#include "ColorDrag.hpp"

#include "../Movable.hpp"

ColorDrag::ColorDrag(float intensity)
	: _intensity(intensity)
{}

void ColorDrag::apply_force(std::vector<Movable>& movables) {
	for (Movable& m : movables)
		apply_force(&m);
}

void ColorDrag::apply_force(Movable* movable) {
	movable->update_color_acceleration(movable->get_color_velocity() * -_intensity);
}
