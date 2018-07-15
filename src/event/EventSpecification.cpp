#include "EventSpecification.hpp"

struct
{
	std::vector<DataSpecification> operator()(const BeatEventSpecification& bes)
	{
		return { BeatDataSpecification(bes.get_min_amplitude()) };
	}
} _needed_data_extractor;

std::vector<DataSpecification> get_needed_data_specifications(const EventSpecification& event_specification)
{
	return std::visit(_needed_data_extractor, event_specification);
}
