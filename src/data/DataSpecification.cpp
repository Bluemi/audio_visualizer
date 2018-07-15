#include "DataSpecification.hpp"

struct
{
	std::vector<DataSpecification> operator()(const BeatDataSpecification&)
	{
		return { AudioDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const AudioDataSpecification&)
	{
		return {};
	}

	std::vector<DataSpecification> operator()(const WriteDataSpecification&)
	{
		return { BeatDataSpecification(0.f) };
	}
} _dependency_resolver;

std::vector<DataSpecification> get_dependencies(const DataSpecification& specification)
{
	return std::visit(_dependency_resolver, specification);
}
