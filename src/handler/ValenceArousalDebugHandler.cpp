#include "ValenceArousalDebugHandler.hpp"

#include <essentia/pool.h>

#include "../data/DataIdentifier.hpp"
#include "entity/EntityIterator.hpp"

void ValenceArousalDebugHandler::update(const essentia::Pool& pool) {
	std::vector<float> arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);
	std::vector<float> valence_timeline = pool.value<std::vector<float>>(data_identifier::VALENCE_TIMELINE);
	std::vector<float> arousal_diffs = pool.value <std::vector<float>>(data_identifier::AROUSAL_DIFFS);

	float arousal_value = 0.f;
	float valence_value = 0.f;
	float arousal_diff = 0.f;

	if (frame_counter < arousal_timeline.size())
		arousal_value = arousal_timeline[frame_counter];

	if (frame_counter < valence_timeline.size())
		valence_value = valence_timeline[frame_counter];

	if (frame_counter < arousal_diffs.size())
		arousal_diff = arousal_diffs[frame_counter];

	const float Y_BASE = 2.f;
	const float SCALE = 4.f;

	unsigned int i = 0;

	for (Movable& m : EntityIterator::iter(entity_buffer)) {
		if (i == 0)
			m.set_position(glm::vec3(0, Y_BASE, 0));
		else if (i == 1)
			m.set_position(glm::vec3(0, Y_BASE, SCALE));
		else if (i == 2)
			m.set_position(glm::vec3(0, Y_BASE+SCALE, 0));
		else if (i == 3)
			m.set_position(glm::vec3(0, Y_BASE+SCALE, SCALE));
		else if (i == 4)
			m.set_position(glm::vec3(0, Y_BASE+SCALE*arousal_value, valence_value*SCALE));
		else if (i == 5)
			m.set_position(glm::vec3(0, Y_BASE+arousal_diff*SCALE, -0.5f));
		else
			break;

		i++;
	}
}
