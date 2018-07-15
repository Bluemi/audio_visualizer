#ifndef __EVENTSPECIFICATION_CLASS__
#define __EVENTSPECIFICATION_CLASS__

#include <variant>

#include "../data/DataSpecification.hpp"

class BeatEventSpecification
{
	public:
		BeatEventSpecification(float min_amplitude) : _min_amplitude(min_amplitude) {}
		float get_min_amplitude() const { return _min_amplitude; }
	private:
		float _min_amplitude;
};

using EventSpecification = std::variant<BeatEventSpecification>;

std::vector<DataSpecification> get_needed_data_specifications(const EventSpecification& event_specification);

#endif
