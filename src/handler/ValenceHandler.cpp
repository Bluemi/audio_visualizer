#include "ValenceHandler.hpp"

#include <essentia/pool.h>

#include <visualizer/entity/movement/RandomColor.hpp>
#include <visualizer/shape/ShapeType.hpp>

#include "../data/DataIdentifier.hpp"

void ValenceHandler::update(const essentia::Pool& pool)
{
	std::vector<float> valence_timeline = pool.value<std::vector<float>>(data_identifier::VALENCE_TIMELINE);

	float value = 0.f;

	if (_frame_counter < valence_timeline.size())
		value = valence_timeline[_frame_counter];

	float b = 0.01f*value;
	float v = 0.01f*value;

	visualizer::Movement sphere_random_color(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(-b, b*3, b)).with_stddev(glm::vec3(v, v, v))));

	unsigned int c = 0;

	for (visualizer::Movable& m : (*_visualizer))
	{
		if (m.get_shape_specification() == visualizer::ShapeType::SPHERE)
		{
			if (c == 0)
			{
				m.add_movement(sphere_random_color);
				glm::vec3 position = m.get_position();
				position.y = 1 + value*2;
				m.set_position(position);
			}
		}
		c = (c+1) % 3;
	}
}
