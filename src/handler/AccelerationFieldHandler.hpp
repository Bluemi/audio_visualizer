#ifndef __ACCELERATIONFIELDHANDLER_CLASS__
#define __ACCELERATIONFIELDHANDLER_CLASS__

#include "BaseHandler.hpp"

#include "entity/movement/AccelerationField.hpp"
#include "entity/movement/PlainForce.hpp"

class BeatEvent;

class AccelerationFieldHandler : public BaseHandler {
	public:
		AccelerationFieldHandler();
		void update(const essentia::Pool& pool);
		void operator()(const BeatEvent& beat_event);
		USE_BASE_OP;
	private:
		AccelerationField _acceleration_field;
		PlainForce _plain_force;
		bool _beat_event_detected;

		static const float TIME_UPDATE;
		static const float AROUSAL_VALUE_SCALE;
		static const float DEFAULT_PLAIN_FORCE;
		static const float BEAT_EVENT_AMPLITUDE_SCALE;
};

#endif
