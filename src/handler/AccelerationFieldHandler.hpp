#ifndef __ACCELERATIONFIELDHANDLER_CLASS__
#define __ACCELERATIONFIELDHANDLER_CLASS__

#include <visualizer/entity/movement/GroupMovement.hpp>

#include "BaseHandler.hpp"

class BeatEvent;

class AccelerationFieldHandler : public BaseHandler
{
	public:
		AccelerationFieldHandler();
		void update(const essentia::Pool& pool);
		void operator()(const BeatEvent& beat_event);
		USE_BASE_OP;
	private:
		visualizer::AccelerationField _acceleration_field;
		visualizer::PlainForce _plain_force;

		static const float TIME_UPDATE;
		static const float AROUSAL_VALUE_SCALE;
		static const float DEFAULT_PLAIN_FORCE;
};

#endif
