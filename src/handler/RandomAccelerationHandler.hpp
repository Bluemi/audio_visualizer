#ifndef __RANDOM_ACCELERATION_HANDLER_CLASS__
#define __RANDOM_ACCELERATION_HANDLER_CLASS__

#include <random>

#include "BaseHandler.hpp"

class RandomAccelerationHandler : public BaseHandler {
	public:
		RandomAccelerationHandler(float strength);
		void update(const essentia::Pool& pool);
		USE_BASE_OP;
	private:
		float _strength;
		std::default_random_engine _random_generator;
		std::uniform_real_distribution<float> _random_distribution;
};

#endif
