#ifndef __BEATEVENTHANDLER_CLASS__
#define __BEATEVENTHANDLER_CLASS__

#include "BaseHandler.hpp"

class BeatEvent;

class BeatEventHandler : public BaseHandler {
	public:
		void operator()(const BeatEvent& beat_event);
		USE_BASE_OP;
};

#endif
