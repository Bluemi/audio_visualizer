#ifndef __CREATION_CLASS__
#define __CREATION_CLASS__

#include "../EntityBuffer.hpp"
#include "NumberGenerator.hpp"
#include "VectorGenerator.hpp"
#include "ShapeGenerator.hpp"

class Creation {
	public:
		Creation(const ShapeGenerator& shape, const std::string& group);

		template<typename Specification>
		Creation(visualizer::ShapeHeap* shape_heap, const Specification& spec, const std::string& group)
			: _quantity(0), _position(), _size(glm::vec3(1.f, 1.f, 1.f)), _shape(shape_heap, spec), _group(group)
		{}

		Creation& with_quantity(const NumberGenerator<unsigned int>& quantity);
		Creation& with_position(const VectorGenerator& position);
		Creation& with_size(const VectorGenerator& size);
		Creation& with_velocity(const VectorGenerator& velocity);
		Creation& with_color(const VectorGenerator& color);
		Creation& with_tag(const std::string& tag);
		Creation& with_shape(const ShapeGenerator& shape);
		Creation& with_group(const std::string& group);

		std::pair<std::string, std::vector<Movable>> create() const;
	private:
		NumberGenerator<unsigned int> _quantity;
		VectorGenerator _position;
		VectorGenerator _size;
		VectorGenerator _velocity;
		ShapeGenerator _shape;
		VectorGenerator _color;
		std::vector<std::string> _tags;
		std::string _group;
};

#endif
