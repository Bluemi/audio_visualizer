#ifndef __HANDLER_CLASS__
#define __HANDLER_CLASS__

#include <vector>
#include <variant>

#include "BeatEventHandler.hpp"
#include "ValenceHandler.hpp"
#include "ArousalHandler.hpp"
#include "ColorHandler.hpp"
#include "ValenceArousalDebugHandler.hpp"

using Handler = std::variant<BeatEventHandler, ValenceHandler, ArousalHandler, ColorHandler, ValenceArousalDebugHandler>;
using HandlerList = std::vector<Handler>;

#endif
