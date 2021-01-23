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
#include "TextHandler.hpp"
#include "RandomAccelerationHandler.hpp"
#include "ImageHandler.hpp"

using Handler = std::variant<
	BeatEventHandler,
	ColorHandler,
	ValenceArousalDebugHandler,
	AccelerationFieldHandler,
	DragHandler,
	LetterHandler,
	TextHandler,
	RandomAccelerationHandler,
	ImageHandler
>;

using HandlerList = std::vector<Handler>;

template<typename T>
HandlerList to_handler_list(const std::vector<T>& handlers) {
	HandlerList handler_list;
	for (const T& t : handlers) {
		handler_list.push_back(t);
	}
	return handler_list;
}

#endif
