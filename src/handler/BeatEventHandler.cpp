#include "BeatEventHandler.hpp"

#include "entity/movement/Movement.hpp"
#include "entity/movement/RandomColor.hpp"
#include "entity/movement/RandomAcceleration.hpp"
#include "entity/EntityIterator.hpp"
#include <visualizer/shape/shape_type.hpp>

#include "../event/BeatEvent.hpp"
#include "../misc/Misc.hpp"

void BeatEventHandler::operator()(const BeatEvent& beat_event) {
	float value = std::pow(beat_event.get_relative_amplitude(), 1.0/3.0);

	float b = 0.01f*value;
	float v = 0.01f*value;
	Movement r_acc(new RandomAcceleration(.4f*value));
	Movement cube_random_color(new RandomColor(VectorGenerator(glm::vec3(b*3, -b, -b)).with_stddev(glm::vec3(v, v, v))));

	for (Movable& m : EntityIterator::iter(entity_buffer)) {
		if (!misc::contains<std::string>(m.get_tags(), "va_debug")) {
			m.add_movement(r_acc);
			m.add_movement(cube_random_color);
		}
	}
}
