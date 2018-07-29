#include "BeatEventHandler.hpp"

#include <iostream>

#include <visualizer/entity/movement/RandomColor.hpp>
#include <visualizer/entity/movement/RandomAcceleration.hpp>
#include <visualizer/shape/ShapeType.hpp>

#include "../event/BeatEvent.hpp"
#include "../misc/Misc.hpp"

void BeatEventHandler::operator()(const BeatEvent& beat_event)
{
	float value = std::pow(beat_event.get_relative_amplitude(), 1.0/3.0);

	float b = 0.01f*value;
	float v = 0.01f*value;
	visualizer::Movement r_acc(new visualizer::RandomAcceleration(.2f*value));
	visualizer::Movement cube_random_color(new visualizer::RandomColor(visualizer::VectorGenerator(glm::vec3(b*3, -b, -b)).with_stddev(glm::vec3(v, v, v))));

	for (auto it = _visualizer->get_entities().begin(); it != _visualizer->get_entities().end(); ++it)
	{
		if (!misc::contains<std::string>((*it).get_tags(), "va_debug"))
		{
			(*it).add_movement(r_acc);
			(*it).add_movement(cube_random_color);
		}
	}
}
