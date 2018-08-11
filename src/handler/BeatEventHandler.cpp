#include "BeatEventHandler.hpp"

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

	for (auto iter = _visualizer->begin(); iter != _visualizer->end(); ++iter)
	{
		if (!misc::contains<std::string>(iter->get_tags(), "va_debug"))
		{
			iter->add_movement(r_acc);
			iter->add_movement(cube_random_color);
		}
	}
}
