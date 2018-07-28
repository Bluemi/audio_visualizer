#ifndef __HANDLER_CLASS__
#define __HANDLER_CLASS__

#include <vector>
#include <variant>

#include "BeatEventHandler.hpp"
#include "ValenceHandler.hpp"
#include "ArousalHandler.hpp"

using Handler = std::variant<BeatEventHandler, ValenceHandler, ArousalHandler>;
using HandlerList = std::vector<Handler>;

#endif
