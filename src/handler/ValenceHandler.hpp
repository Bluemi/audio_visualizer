#ifndef __VALENCEHANDLER_CLASS__
#define __VALENCEHANDLER_CLASS__

#include "BaseHandler.hpp"

class ValenceHandler : public BaseHandler
{
	public:
		void update(const essentia::Pool& pool);
};

#endif
