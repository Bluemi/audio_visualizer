#ifndef __SHAPEGENERATOR_CLASS__
#define __SHAPEGENERATOR_CLASS__

#include <vector>

#include <visualizer/shape/shape.hpp>
#include <visualizer/shape/shape_specification.hpp>

struct _ShapeShare {
	_ShapeShare(const visualizer::ShapeSpecification& spec, float s) : specification(spec), share(s) {}

	visualizer::ShapeSpecification specification;
	float share;
};

namespace visualizer {
	class ShapeHeap;
}

class ShapeGenerator {
	public:
		ShapeGenerator(visualizer::ShapeHeap* shape_heap, const visualizer::ShapeSpecification& shape);
		ShapeGenerator(visualizer::ShapeHeap* shape_heap, const visualizer::ShapeSpecification& shape, float share);

		ShapeGenerator& with_shape(const visualizer::ShapeSpecification& shape);
		ShapeGenerator& with_shape(const visualizer::ShapeSpecification& shape, float share);

		visualizer::Shape get() const;
	private:
		void generate_sum();

		std::vector<_ShapeShare> _shapes;
		float _sum;
		visualizer::ShapeHeap* _shape_heap;
};

#endif
