#include "ArousalHandler.hpp"

#include <essentia/pool.h>

#include <visualizer/entity/movement/RandomColor.hpp>
#include <visualizer/shape/ShapeType.hpp>

#include "../data/DataIdentifier.hpp"

void ArousalHandler::update(const essentia::Pool& pool)
{
	std::vector<float> arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);

	float value = 0.f;

	if (_frame_counter < arousal_timeline.size())
		value = arousal_timeline[_frame_counter];

	float b = 0.01f*value;
	float v = 0.01f*value;

	visualizer::Movement sphere_random_color(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(b*3, b*3, -b)).with_stddev(glm::vec3(v, v, v))));

	unsigned int c = 1;

	for (auto it = _visualizer->get_entities().begin(); it != _visualizer->get_entities().end(); ++it)
	{
		if ((*it).get_shape_specification() == visualizer::ShapeType::SPHERE)
		{
			if (c == 0)
			{
				(*it).add_movement(sphere_random_color);
				glm::vec3 position = (*it).get_position();
				position.y = 1 + value*2;
				(*it).set_position(position);
			}
		}
		c = (c+1) % 3;
	}
}
