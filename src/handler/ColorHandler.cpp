#include "ColorHandler.hpp"

#include <essentia/pool.h>

#include <visualizer/entity/movement/ColorTarget.hpp>
#include <visualizer/shape/ShapeType.hpp>

#include "../data/DataIdentifier.hpp"
#include "../misc/Misc.hpp"

std::vector<ColorHandler::_Color> ColorHandler::_colors {
	ColorHandler::_Color(glm::vec3(255.f/255.f, 0.f/255.f,   0.f/255.f),   glm::vec2(0.85, 0.4), 1), // Red
	ColorHandler::_Color(glm::vec3(248.f/255.f, 230.f/255.f, 9.f/255.f),   glm::vec2(0.8, 0.7),  1),  // Yellow
	ColorHandler::_Color(glm::vec3(0.f/255.f,   242.f/255.f, 28.f/255.f),  glm::vec2(0.3, 0.8),  1),  // Green
	ColorHandler::_Color(glm::vec3(0.f/255.f,   242.f/255.f, 28.f/255.f),  glm::vec2(0.1, 0.8),  1.8),  // Green
	ColorHandler::_Color(glm::vec3(5.f/255.f,   8.f/255.f,   255.f/255.f), glm::vec2(0.0, 0.4),  2.0),  // Blue
	ColorHandler::_Color(glm::vec3(20.f/255.f, 80.f/255.f, 100.f/255.f), glm::vec2(0.2, 0.3),  2.5),  // Gray
	ColorHandler::_Color(glm::vec3(0.f/255.f,   0.f/255.f,   0.f/255.f),   glm::vec2(0.9, 0.0),  1),  // Black
	ColorHandler::_Color(glm::vec3(0.f/255.f,   0.f/255.f,   0.f/255.f),   glm::vec2(0.7, 0.0),  1),  // Black
	ColorHandler::_Color(glm::vec3(0.f/255.f,   0.f/255.f,   0.f/255.f),   glm::vec2(0.5, 0.0),  4.7),  // Black
	ColorHandler::_Color(glm::vec3(0.f/255.f,   0.f/255.f,   0.f/255.f),   glm::vec2(0.3, 0.0),  0.7),  // Black
	ColorHandler::_Color(glm::vec3(151.f/255.f, 69.f/255.f,  3.f/255.f),   glm::vec2(0.5, 0.5),  1.7)
};

ColorHandler::ColorHandler(float strength, float std_dev)
	: _strength(strength)
{
	_color_gen.with_stddev(glm::vec3(std_dev, std_dev, std_dev));
}

void ColorHandler::update(const essentia::Pool& pool) {
	std::vector<float> arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);
	std::vector<float> valence_timeline = pool.value<std::vector<float>>(data_identifier::VALENCE_TIMELINE);

	float arousal_value = 0.f;
	float valence_value = 0.f;

	if (_frame_counter < arousal_timeline.size())
		arousal_value = arousal_timeline[_frame_counter];

	if (_frame_counter+10 < valence_timeline.size())
		valence_value = valence_timeline[_frame_counter+10];

	glm::vec2 emotion(arousal_value, valence_value);

	glm::vec3 color = calculate_color(emotion);

	_color_gen.with_mean(color);

	for (visualizer::Movable& m : (*_visualizer)) {
		if (!misc::contains<std::string>(m.get_tags(), "va_debug")) {
			visualizer::Movement sphere_target_color(new visualizer::ColorTarget(_color_gen.get(), _strength));
			m.add_movement(sphere_target_color);
		}
	}
}

glm::vec3 ColorHandler::calculate_color(const glm::vec2& emotion) {
	std::vector<float> influences = get_influences(emotion, _colors);

	glm::vec3 color(0.f, 0.f, 0.f);

	for (unsigned int i = 0; i < _colors.size(); i++) {
		color += _colors[i].color * influences[i];
	}

	return color;
}

float _sqr(float f) {
	return f*f;
}

const float MIN_DISTANCE = 0.001f;

std::vector<float> ColorHandler::get_influences(const glm::vec2& emotion, const std::vector<_Color>& colors) {
	std::vector<float> influences;
	for (const _Color& color : colors) {
		float distance = glm::length(emotion - color.center);
		influences.push_back(color.strength/(std::pow(distance, 5.0)+MIN_DISTANCE));
	}

	double sum = 0.0;

	for (float f : influences)
		sum += f;

	for (float& f : influences)
		f /= sum;

	return influences;
}
