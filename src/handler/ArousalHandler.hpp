#ifndef __AROUSALHANDLER_CLASS__
#define __AROUSALHANDLER_CLASS__

#include "BaseHandler.hpp"

class ArousalHandler : public BaseHandler
{
	public:
		void update(const essentia::Pool& pool);
};

#endif
