#include "ShapeGenerator.hpp"

#include <iostream>

#include <visualizer/shape/shape_heap.hpp>

const float DEFAULT_SHARE = 1.f;

ShapeGenerator::ShapeGenerator(visualizer::ShapeHeap* shape_heap, const visualizer::ShapeSpecification& shape)
	: _shapes{_ShapeShare(shape, DEFAULT_SHARE)}, _shape_heap(shape_heap)
{
	generate_sum();
}

ShapeGenerator::ShapeGenerator(visualizer::ShapeHeap* shape_heap, const visualizer::ShapeSpecification& shape, float share)
	: _shapes{_ShapeShare(shape, share)}, _shape_heap(shape_heap)
{
	generate_sum();
}

ShapeGenerator& ShapeGenerator::with_shape(const visualizer::ShapeSpecification& shape) {
	_shapes.push_back(_ShapeShare(shape, DEFAULT_SHARE));
	generate_sum();
	return *this;
}

ShapeGenerator& ShapeGenerator::with_shape(const visualizer::ShapeSpecification& shape, float share) {
	_shapes.push_back(_ShapeShare(shape, share));
	generate_sum();
	return *this;
}

visualizer::Shape ShapeGenerator::get() const {
	if (_shapes.size() == 1) {
		return _shape_heap->get_shape(_shapes[0].specification);
	}

	float number = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX/_sum));

	float counter = 0.f;
	for (const _ShapeShare& ss : _shapes) {
		counter += ss.share;
		if (counter >= number) {
			return _shape_heap->get_shape(ss.specification);
		}
	}
	return _shape_heap->get_shape(_shapes[_shapes.size()-1].specification);
}

void ShapeGenerator::generate_sum() {
	_sum = 0.f;
	for (const _ShapeShare& ss : _shapes) {
		_sum += ss.share;
	}
}
