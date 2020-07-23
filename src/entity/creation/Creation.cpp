#include "Creation.hpp"

#include <vector>

#include "../Movable.hpp"
#include <visualizer/shape/shape_initialization.hpp>

Creation::Creation(const ShapeGenerator& shape, const std::string& group)
	: _quantity(0), _position(), _size(glm::vec3(1.f, 1.f, 1.f)), _shape(shape), _group(group)
{}

Creation& Creation::with_quantity(const NumberGenerator<unsigned int>& quantity) {
	_quantity = quantity;
	return *this;
}

Creation& Creation::with_position(const VectorGenerator& position) {
	_position = position;
	return *this;
}

Creation& Creation::with_size(const VectorGenerator& size) {
	_size = size;
	return *this;
}

Creation& Creation::with_velocity(const VectorGenerator& velocity) {
	_velocity = velocity;
	return *this;
}

Creation& Creation::with_color(const VectorGenerator& color) {
	_color = color;
	return *this;
}

Creation& Creation::with_tag(const std::string& tag) {
	_tags.push_back(tag);
	return *this;
}

Creation& Creation::with_shape(const ShapeGenerator& shape) {
	_shape = shape;
	return *this;
}

Creation& Creation::with_group(const std::string& group) {
	_group = group;
	return *this;
}

std::pair<std::string, std::vector<Movable>> Creation::create() const {
	unsigned int quantity = _quantity.get();

	std::vector<Movable> movables;
	movables.reserve(quantity);

	for (unsigned int i = 0; i < quantity; i++) {
		Movable m(_shape.get());
		m.set_position(_position.get());
		m.set_size(_size.get());
		m.set_velocity(_velocity.get());
		m.set_color(_color.get());
		m.set_tags(_tags);

		movables.push_back(m);
	}

	return {_group, movables};
}
