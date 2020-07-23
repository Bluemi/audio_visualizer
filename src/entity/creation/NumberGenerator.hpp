#ifndef __NUMBERGENERATOR_CLASS__
#define __NUMBERGENERATOR_CLASS__

#include "../../misc/Misc.hpp"

template<typename NumberType>
class NumberGenerator {};

template<>
class NumberGenerator<float> {
	public:
		NumberGenerator() : _mean(0.f), _stddev(0.f) {}

		NumberGenerator<float>& with_mean(float mean) {
			_mean = mean;
			return *this;
		}

		NumberGenerator<float>& with_stddev(float stddev) {
			_stddev = stddev;
			return *this;
		}

		float get() const {
			return misc::generate_float(_mean, _stddev);
		}
	private:
		float _mean;
		float _stddev;
};

template<>
class NumberGenerator<unsigned int> {
	public:
		NumberGenerator() : _min(0), _max(0) {}
		NumberGenerator(unsigned int number) : _min(number), _max(number) {}

		NumberGenerator<unsigned int>& with_min(unsigned int min) {
			_min = min;
			return *this;
		}

		NumberGenerator<unsigned int>& with_max(unsigned int max) {
			_max = max;
			return *this;
		}

		unsigned int get() const {
			return misc::generate_uint(_min, _max);
		}
	private:
		unsigned int _min;
		unsigned int _max;
};

#endif
