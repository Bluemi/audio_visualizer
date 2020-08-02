#include "LetterHandler.hpp"

#include <visualizer/shape/shape_heap.hpp>

#include "entity/movement/GroupMovement.hpp"
#include "entity/creation/Creation.hpp"

LetterHandler::LetterHandler(char letter) : _letter_movement(letter), _letter(letter) {}

void LetterHandler::init(visualizer::ShapeHeap& shape_heap) {
	std::string group("letters");
	group.push_back(_letter);

	groups.push_back(group);

	ShapeGenerator shape_gen(&shape_heap, visualizer::CubeSpecification(), 1.f);
	VectorGenerator pos_gen = VectorGenerator().with_stddev(glm::vec3(5.f, 0.5f, 5.f));
	VectorGenerator size_gen = VectorGenerator(glm::vec3(0.15f, 0.15f, 0.15f)).with_stddev(glm::vec3(0.01f));
	VectorGenerator speed_gen = VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));

	Creation creation = Creation(shape_gen, group)
		.with_quantity(400)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	entity_buffer->insert(creation.create());
}

void LetterHandler::update(const essentia::Pool& pool) {
	GroupMovement::apply_group_movement_to(entity_buffer, _letter_movement, groups);
}
