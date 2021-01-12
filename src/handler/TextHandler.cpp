#include "TextHandler.hpp"

#include "entity/movement/GroupMovement.hpp"
#include <visualizer/shape/shape_type.hpp>
#include "entity/creation/Creation.hpp"
#include "../event/TextEvent.hpp"

constexpr float LETTER_WIDTH = 10.0f;
constexpr float MAX_MAGNITUDE = 0.1f;
constexpr float MAX_EXPLOSION_MAGNITUDE = 1.0f;

TextHandler::TextHandler(unsigned int max_letters)
	: _max_letters(max_letters), _initialized(false), _random_distribution(-10.f, 10.f)
{}

void TextHandler::init(visualizer::ShapeHeap& shape_heap) {
	ShapeGenerator shape_gen(&shape_heap, visualizer::CubeSpecification(), 1.f);
	VectorGenerator pos_gen = VectorGenerator().with_mean(glm::vec3(0.f, 0.f, 80.f)).with_stddev(glm::vec3(5.f, 0.5f, 40.f));
	VectorGenerator size_gen = VectorGenerator(glm::vec3(0.15f, 0.15f, 0.15f)).with_stddev(glm::vec3(0.02f));
	VectorGenerator speed_gen = VectorGenerator().with_stddev(glm::vec3(1.f, 1.f, 1.f));

	for (unsigned int i = 0; i < _max_letters; i++) {
		std::string letter_group_name = "letter" + std::to_string(i);
		Creation letter_creation = Creation(shape_gen, letter_group_name)
			.with_quantity(500)
			.with_position(pos_gen)
			.with_size(size_gen)
			.with_velocity(speed_gen);
		entity_buffer->insert(letter_creation.create());
	}
}

void TextHandler::update(const essentia::Pool& pool) {
	if (_initialized) {
		float z_pos = 0.f;
		for (unsigned int i = 0; i < _max_letters; i++) {
			std::string group = "letter" + std::to_string(i);
			if (i < _current_text.size() && _current_text[i] != ' ') {
				char c = _current_text[i];
				std::vector<std::string> groups {group};
				LetterMovement letter_movement(c, LETTER_WIDTH);
				letter_movement.set_position(glm::vec3(0.f, 0.f, z_pos));
				GroupMovement::apply_group_movement_to(entity_buffer, letter_movement, groups);
			} else {
				auto movables = entity_buffer->find(group);
				if (movables != entity_buffer->end()) {
					for (Movable& movable : movables->second) {
						movable.update_color_acceleration(glm::vec3(-0.01f, -0.01f, -0.01f));
					}
				} else {
					std::cerr << "Could not find group \"" << group << "\" but required by TextHandler movement" << std::endl;
				}
			}
			if (i < _current_text.size()) {
				z_pos += 1.2f * get_letter_width(_current_text[i]) * LETTER_WIDTH;
			}
		}
	} else {
		for (unsigned int i = 0; i < _max_letters; i++) {
			std::string group = "letter" + std::to_string(i);
			auto movables = entity_buffer->find(group);
			if (movables != entity_buffer->end()) {
				for (Movable& movable : movables->second) {
					glm::vec3 target_point = glm::vec3(0.f, 0.f, i*LETTER_WIDTH*0.5f);

					glm::vec3 dir = target_point - movable.get_position();
					glm::vec3 update = dir - movable.get_velocity();

					if (glm::length(update) > MAX_MAGNITUDE) {
						update *= MAX_MAGNITUDE / glm::length(update);
					}

					movable.update_acceleration(update);
				}
			} else {
				std::cerr << "Could not find group \"" << group << "\" but required by TextHandler movement" << std::endl;
			}
		}
	}
}

void TextHandler::operator()(const TextEvent& text_event) {
	std::string old_text = _current_text;
	_current_text = text_event.get_text();
	if (text_event.is_exploding()) {
		for (unsigned int i = 0; i < old_text.size(); i++) {
			if (old_text[i] != ' ' && (i >= _current_text.size() || _current_text[i] == ' ')) {
				std::string group_name("letter" + std::to_string(i));
				auto movables = entity_buffer->find(group_name);
				if (movables != entity_buffer->end()) {
					for (Movable& movable : movables->second) {
						glm::vec3 dir = glm::vec3(_random_distribution(_random_generator), _random_distribution(_random_generator), _random_distribution(_random_generator));
						glm::vec3 update = dir - movable.get_velocity();

						if (glm::length(update) > MAX_EXPLOSION_MAGNITUDE) {
							update *= MAX_EXPLOSION_MAGNITUDE / glm::length(update);
						}

						movable.update_acceleration(update);
					}
				} else {
					std::cerr << "Could not find group \"" << group_name << "\" but required by TextHandler movement" << std::endl;
				}
			}
		}
	}
	_initialized = true;
}
