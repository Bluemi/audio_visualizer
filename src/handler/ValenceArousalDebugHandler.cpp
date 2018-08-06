#include "ValenceArousalDebugHandler.hpp"

#include <essentia/pool.h>

#include "../data/DataIdentifier.hpp"

void ValenceArousalDebugHandler::update(const essentia::Pool& pool)
{
	std::vector<float> arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);
	std::vector<float> valence_timeline = pool.value<std::vector<float>>(data_identifier::VALENCE_TIMELINE);
	std::vector<float> arousal_diffs = pool.value <std::vector<float>>(data_identifier::AROUSAL_DIFFS);

	float arousal_value = 0.f;
	float valence_value = 0.f;
	float arousal_diff = 0.f;

	if (_frame_counter < arousal_timeline.size())
		arousal_value = arousal_timeline[_frame_counter];

	if (_frame_counter < valence_timeline.size())
		valence_value = valence_timeline[_frame_counter];

	if (_frame_counter < arousal_diffs.size())
		arousal_diff = arousal_diffs[_frame_counter];

	std::vector<visualizer::Movable>& movables = _visualizer->get_entities().get_movables();

	const float Y_BASE = 2.f;
	const float SCALE = 4.f;

	for (unsigned int i = 0; i < movables.size(); i++)
	{
		if (i == 0)
			movables[i].set_position(glm::vec3(0, Y_BASE, 0));
		else if (i == 1)
			movables[i].set_position(glm::vec3(0, Y_BASE, SCALE));
		else if (i == 2)
			movables[i].set_position(glm::vec3(0, Y_BASE+SCALE, 0));
		else if (i == 3)
			movables[i].set_position(glm::vec3(0, Y_BASE+SCALE, SCALE));
		else if (i == 4)
			movables[i].set_position(glm::vec3(0, Y_BASE+SCALE*arousal_value, valence_value*SCALE));
		else if (i == 5)
			movables[i].set_position(glm::vec3(0, Y_BASE+arousal_diff*SCALE, -0.5f));
		else
			break;
	}
}
