#include "RandomColor.hpp"

#include "../Movable.hpp"

RandomColor::RandomColor(const VectorGenerator& color_gen)
	: _color_gen(color_gen), _used(false)
{}

void RandomColor::apply_force(Movable* movable) {
	if (!_used) {
		movable->update_color_acceleration(_color_gen.get());
		_used = true;
	}
}

bool RandomColor::should_be_removed() const {
	return _used;
}
