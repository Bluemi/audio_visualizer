#include "InformationBuilder.hpp"

#include "../misc/Misc.hpp"
#include "../data/DataGeneratorParameterProvider.hpp"

InformationBuilder::InformationBuilder(const std::string& filename)
	: _filename(filename)
{
	essentia::init();
	_algorithm_factory = &essentia::standard::AlgorithmFactory::instance();
}

InformationBuilder::~InformationBuilder()
{
	essentia::shutdown();
}

InformationBuilder& InformationBuilder::with_events(const std::vector<EventSpecification>& targets)
{
	_target_events.insert(_target_events.end(), targets.cbegin(), targets.cend());
	return *this;
}

InformationBuilder& InformationBuilder::with_data(const std::vector<DataSpecification>& targets)
{
	_target_data.insert(_target_data.end(), targets.cbegin(), targets.cend());
	return *this;
}

std::optional<InformationContainer> InformationBuilder::build()
{
	// generate DataSpecifications
	std::vector<DataSpecification> data_specifications = get_event_specification_dependencies(_target_events);
	data_specifications.insert(data_specifications.end(), _target_data.cbegin(), _target_data.cend());
	data_specifications = get_data_specification_dependencies(data_specifications);

	// generate DataGenerators
	std::vector<DataGenerator> data_generators = create_data_generators(data_specifications);
	provide_data_generator_parameters(&data_generators);
	bool success = compute_data_generators(&data_generators);

	if (!success)
	{
		return {};
	}

	std::vector<EventGenerator> event_generators = create_event_generators(_target_events);
	EventList event_list = compute_event_generators(event_generators);
	std::sort(event_list.begin(), event_list.end());

	return InformationContainer(event_list, _pool);
}

std::vector<DataSpecification> InformationBuilder::get_event_specification_dependencies(const std::vector<EventSpecification>& event_specifications) const
{
	std::vector<DataSpecification> data_specifications;
	for (const EventSpecification& event_spec : event_specifications)
	{
		std::vector<DataSpecification> tmp = get_needed_data_specifications(event_spec);
		data_specifications.insert(data_specifications.end(), tmp.cbegin(), tmp.cend());
	}

	return data_specifications;
}

const unsigned int EMERGENCY_BREAK_SIZE = 10000;

std::vector<DataSpecification> InformationBuilder::get_data_specification_dependencies(const std::vector<DataSpecification>& data_specifications) const
{
	std::vector<DataSpecification> reverse_dependencies = data_specifications;

	for (unsigned int i = 0; i < reverse_dependencies.size(); i++)
	{
		std::vector<DataSpecification> tmp = get_dependencies(reverse_dependencies[i]);
		reverse_dependencies.insert(reverse_dependencies.end(), tmp.cbegin(), tmp.cend());

		if (reverse_dependencies.size() > EMERGENCY_BREAK_SIZE)
		{
			break;
		}
	}

	std::vector<DataSpecification> dependencies;

	for (auto it = reverse_dependencies.crbegin(); it != reverse_dependencies.crend(); ++it)
	{
		if (!misc::contains(dependencies, *it))
		{
			dependencies.push_back(*it);
		}
	}

	return dependencies;
}

std::vector<DataGenerator> InformationBuilder::create_data_generators(const std::vector<DataSpecification>& data_specifications)
{
	std::vector<DataGenerator> generators;
	for (const auto& spec : data_specifications)
	{
		generators.push_back(create_generator(&_pool, _algorithm_factory, spec));
	}
	return generators;
}

void InformationBuilder::provide_data_generator_parameters(std::vector<DataGenerator>* data_generators) const
{
	DataGeneratorParameterProvider dgpp(_filename);

	for (DataGenerator& dg : *data_generators)
		dgpp.provide(&dg);
}

bool InformationBuilder::compute_data_generators(std::vector<DataGenerator>* generators)
{
	for (auto& g : *generators)
	{
		try {
			compute_generator(g);
		} catch (essentia::EssentiaException e) {
			std::cout << "Error.\n\n" << e.what() << std::endl;
			return false;
		}
	}
	return true;
}

std::vector<EventGenerator> InformationBuilder::create_event_generators(const std::vector<EventSpecification>& event_specifications) const
{
	std::vector<EventGenerator> event_generators;

	for (const EventSpecification& event_spec : event_specifications)
		event_generators.push_back(create_event_generator(event_spec));

	return event_generators;
}

EventList InformationBuilder::compute_event_generators(const std::vector<EventGenerator>& event_generators) const
{
	EventList event_list;
	for (const EventGenerator& eg : event_generators)
	{
		EventList tmp = compute_event_generator(eg, _pool);
		event_list.insert(event_list.end(), tmp.cbegin(), tmp.cend());
	}

	return event_list;
}
