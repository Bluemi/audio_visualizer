#ifndef __INFORMATIONBUILDER_CLASS__
#define __INFORMATIONBUILDER_CLASS__

#include <essentia/pool.h>
#include <essentia/algorithmfactory.h>

#include "InformationContainer.hpp"
#include "../event/Event.hpp"
#include "../data/DataSpecification.hpp"
#include "../event/EventSpecification.hpp"
#include "../generators/data/DataGenerator.hpp"
#include "../generators/event/EventGenerator.hpp"

class InformationBuilder {
	public:
		InformationBuilder(const std::string& filename);
		~InformationBuilder();
		InformationBuilder& with_events(const std::vector<EventSpecification>& targets);
		InformationBuilder& with_data(const std::vector<DataSpecification>& targets);

		std::optional<InformationContainer> build();
	private:
		std::vector<DataSpecification> get_event_specification_dependencies(const std::vector<EventSpecification>& event_specifications) const;

		/**
		 * Returns a vector of all specifications given and the recursive dependencies of these specifications.
		 */
		std::vector<DataSpecification> get_data_specification_dependencies(const std::vector<DataSpecification>& data_specifications) const;

		std::vector<DataGenerator> create_data_generators(const std::vector<DataSpecification>& data_specifications);
		void provide_data_generator_parameters(std::vector<DataGenerator>* data_generators) const;
		bool compute_data_generators(std::vector<DataGenerator>* generators);

		std::vector<EventGenerator> create_event_generators(const std::vector<EventSpecification>& event_specifications) const;
		EventList compute_event_generators(const std::vector<EventGenerator>& event_generators) const;

		std::vector<EventSpecification> _target_events;
		std::vector<DataSpecification> _target_data;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
		essentia::Pool _pool;
		std::string _filename;
};

#endif
