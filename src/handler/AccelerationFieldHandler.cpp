#include "AccelerationFieldHandler.hpp"

#include <essentia/pool.h>

#include "entity/movement/GroupMovement.hpp"
#include "../event/BeatEvent.hpp"
#include "../data/DataIdentifier.hpp"

const float AccelerationFieldHandler::TIME_UPDATE = 0.03f;
const float AccelerationFieldHandler::AROUSAL_VALUE_SCALE = 0.02f;
const float AccelerationFieldHandler::DEFAULT_PLAIN_FORCE = 0.001f;
const float AccelerationFieldHandler::BEAT_EVENT_AMPLITUDE_SCALE = 0.25f;

AccelerationFieldHandler::AccelerationFieldHandler()
	: _plain_force(DEFAULT_PLAIN_FORCE), _beat_event_detected(false)
{}

void AccelerationFieldHandler::update(const essentia::Pool& pool) {
	const std::vector<float>& arousal_timeline = pool.value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);

	float arousal_value = 0.f;
	if (frame_counter < arousal_timeline.size())
		arousal_value = arousal_timeline[frame_counter];

	_acceleration_field.update_time(TIME_UPDATE);
	if (!_beat_event_detected)
		_acceleration_field.set_force(arousal_value * AROUSAL_VALUE_SCALE);
	_beat_event_detected = false;

	GroupMovement::apply_group_movement_to(entity_buffer, _acceleration_field, groups);

	_plain_force.set_strength(arousal_value*0.01f);
	GroupMovement::apply_group_movement_to(entity_buffer, _plain_force, groups);
}

void AccelerationFieldHandler::operator()(const BeatEvent& beat_event) {
	const float new_force = std::sqrt(beat_event.get_relative_amplitude()) * BEAT_EVENT_AMPLITUDE_SCALE;
	if (new_force > _acceleration_field.get_force()) {
		_acceleration_field.set_force(new_force);
		_beat_event_detected = true;
	}
}
