#include "EventSpecification.hpp"

struct {
	std::vector<DataSpecification> operator()(const TickEventSpecification& bes) {
		return { TickDataSpecification(bes.get_min_amplitude()) };
	}

	std::vector<DataSpecification> operator()(const BeatEventSpecification&) {
		return { BarkBandsDifferenceDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const ArousalEventSpecification&) {
		return { ArousalDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const ValenceEventSpecification&) {
		return { ValenceDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const TextEventSpecification&) {
		return {};
	}
} _needed_data_extractor;

std::vector<DataSpecification> get_needed_data_specifications(const EventSpecification& event_specification) {
	return std::visit(_needed_data_extractor, event_specification);
}
