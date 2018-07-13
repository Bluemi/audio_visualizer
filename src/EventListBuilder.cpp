#include "EventListBuilder.hpp"

#include "misc/Misc.hpp"

EventListBuilder::EventListBuilder()
{
	essentia::init();
	_algorithm_factory = &essentia::standard::AlgorithmFactory::instance();
}

EventListBuilder::~EventListBuilder()
{
	essentia::shutdown();
}

EventListBuilder& EventListBuilder::with_targets(const std::vector<EventSpecification>& targets)
{
	_targets.insert(_targets.end(), targets.cbegin(), targets.cend());
	return *this;
}

EventList EventListBuilder::build()
{
	std::vector<EventSpecification> targets = get_specification_dependencies(_targets);
	std::vector<Generator> generators = build_generators(targets);
	compute_generators(&generators);
	return EventList();
}

const unsigned int EMERGENCY_BREAK_SIZE = 10000;

std::vector<EventSpecification> EventListBuilder::get_specification_dependencies(const std::vector<EventSpecification>& specifications) const
{
	std::vector<EventSpecification> reverse_dependencies = specifications;

	for (unsigned int i = 0; i < reverse_dependencies.size(); i++)
	{
		std::vector<EventSpecification> tmp = get_dependencies(reverse_dependencies[i]);
		reverse_dependencies.insert(reverse_dependencies.end(), tmp.cbegin(), tmp.cend());

		if (reverse_dependencies.size() > EMERGENCY_BREAK_SIZE)
		{
			break;
		}
	}

	std::vector<EventSpecification> dependencies;

	for (auto it = reverse_dependencies.crbegin(); it != reverse_dependencies.crend(); ++it)
	{
		if (!misc::contains(dependencies, *it))
		{
			dependencies.push_back(*it);
		}
	}

	return dependencies;
}

std::vector<Generator> EventListBuilder::build_generators(const std::vector<EventSpecification>& specifications)
{
	std::vector<Generator> generators;
	for (const auto& spec : specifications)
	{
		generators.push_back(build_generator(&_pool, _algorithm_factory, spec));
	}
	return generators;
}

void EventListBuilder::compute_generators(std::vector<Generator>* generators)
{
	for (auto& i : *generators)
	{
		compute_generator(i);
	}
}
