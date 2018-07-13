#ifndef __EVENTLISTBUILDER_CLASS__
#define __EVENTLISTBUILDER_CLASS__

#include <essentia/pool.h>
#include <essentia/algorithmfactory.h>

#include "event/Event.hpp"
#include "event/EventSpecification.hpp"
#include "generator/Generator.hpp"

class EventListBuilder
{
	public:
		EventListBuilder();
		~EventListBuilder();
		EventListBuilder& with_targets(const std::vector<EventSpecification>& targets);

		EventList build();
	private:
		/**
		 * Returns a vector of all specifications given and
		 * the recursive dependencies of these specifications.
		 */
		std::vector<EventSpecification> get_specification_dependencies(const std::vector<EventSpecification>& specifications) const;
		std::vector<Generator> build_generators(const std::vector<EventSpecification>& specifications);
		void compute_generators(std::vector<Generator>* generators);
		EventList data_to_event_list() const;

		std::vector<EventSpecification> _targets;
		essentia::standard::AlgorithmFactory* _algorithm_factory;
		essentia::Pool _pool;
};

#endif
