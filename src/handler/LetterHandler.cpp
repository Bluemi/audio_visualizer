#include "LetterHandler.hpp"

#include <visualizer/shape/shape_heap.hpp>

#include "entity/movement/GroupMovement.hpp"
#include "entity/creation/Creation.hpp"

LetterHandler::LetterHandler(char letter, int id) : _letter_movement(letter, 10.f), _letter(letter), _id(id) {}

LetterHandler::LetterHandler(char letter, int id, float scale) : _letter_movement(letter, scale), _letter(letter), _id(id) {}

void LetterHandler::init(visualizer::ShapeHeap& shape_heap) {
	std::string group = "letters";
	group = group + std::to_string(_id);
	group.push_back(_letter);

	groups.push_back(group);

	ShapeGenerator shape_gen(&shape_heap, visualizer::CubeSpecification(), 1.f);
	VectorGenerator pos_gen = VectorGenerator(_letter_movement.get_position()).with_stddev(glm::vec3(5.f, 0.5f, 5.f));
	VectorGenerator size_gen = VectorGenerator(glm::vec3(0.15f, 0.15f, 0.15f)).with_stddev(glm::vec3(0.01f));
	VectorGenerator speed_gen = VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));

	Creation creation = Creation(shape_gen, group)
		.with_quantity(700)
		.with_position(pos_gen)
		.with_size(size_gen)
		.with_velocity(speed_gen);

	entity_buffer->insert(creation.create());
}

void LetterHandler::update(const essentia::Pool& pool) {
	GroupMovement::apply_group_movement_to(entity_buffer, _letter_movement, groups);
}

void LetterHandler::set_position(const glm::vec3& position) {
	_letter_movement.set_position(position);
}

void LetterHandler::set_scale(float scale) {
	_letter_movement.set_scale(scale);
}

std::vector<LetterHandler> create_string_handlers(const std::string& text, const glm::vec3& position, float scale) {
	std::vector<LetterHandler> handlers;
	float z_pos = 0.f;
	int id = 0;
	for (char c : text) {
		if (c != ' ') {
			LetterHandler handler(c, id, scale);
			handler.set_position(position + glm::vec3(0.f, 0.f, z_pos));
			handlers.push_back(handler);
			id++;
		}
		z_pos += 1.2f * get_letter_width(c) * scale;
	}
	return handlers;
}
