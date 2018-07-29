#ifndef __VALENCEAROUSALDEBUGHANDLER_CLASS__
#define __VALENCEAROUSALDEBUGHANDLER_CLASS__

#include "BaseHandler.hpp"

class ValenceArousalDebugHandler : public BaseHandler
{
	public:
		void update(const essentia::Pool& pool);
};

#endif
