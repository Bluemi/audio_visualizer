#include "EventSpecification.hpp"

struct
{
	std::vector<EventSpecification> operator()(const BeatEventSpecification& spec)
	{
		return { AudioEventSpecification(spec.get_filename()) };
	}
	std::vector<EventSpecification> operator()(const AudioEventSpecification& spec)
	{
		return {};
	}

} _dependency_resolver;

std::vector<EventSpecification> get_dependencies(const EventSpecification& specification)
{
	return std::visit(_dependency_resolver, specification);
}
