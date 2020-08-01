#ifndef __HANDLER_CLASS__
#define __HANDLER_CLASS__

#include <vector>
#include <variant>

#include "BeatEventHandler.hpp"
#include "ColorHandler.hpp"
#include "ValenceArousalDebugHandler.hpp"
#include "AccelerationFieldHandler.hpp"
#include "DragHandler.hpp"
#include "LetterHandler.hpp"

using Handler = std::variant<
	BeatEventHandler,
	ColorHandler,
	ValenceArousalDebugHandler,
	AccelerationFieldHandler,
	DragHandler,
	LetterHandler
>;

using HandlerList = std::vector<Handler>;

#endif
