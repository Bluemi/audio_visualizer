#include "EventGenerator.hpp"

#include "../../event/EventSpecification.hpp"

struct {
	EventGenerator operator()(const TickEventSpecification&) {
		return TickEventGenerator();
	}

	EventGenerator operator()(const BeatEventSpecification& beat_event_specification) {
		return BeatEventGenerator(beat_event_specification._accelerations);
	}

	EventGenerator operator()(const ArousalEventSpecification&) {
		return ArousalEventGenerator();
	}

	EventGenerator operator()(const ValenceEventSpecification&) {
		return ValenceEventGenerator();
	}

	EventGenerator operator()(const TextEventSpecification& specification) {
		return TextEventGenerator(specification.get_texts());
	}

	EventGenerator operator()(const ImageEventSpecification& specification) {
		return ImageEventGenerator(specification.image_id, specification.start_time, specification.end_time);
	}
} _generator_creator;

EventGenerator create_event_generator(const EventSpecification& event_specification) {
	return std::visit(_generator_creator, event_specification);
}

struct GeneratorComputer {
	GeneratorComputer(const essentia::Pool& pool) : _pool(&pool) {}

	template<typename GeneratorType>
	EventList operator()(const GeneratorType& generator) const {
		return generator.compute(*_pool);
	}

	private:
		const essentia::Pool* _pool;
};

EventList compute_event_generator(const EventGenerator& generator, const essentia::Pool& pool) {
	GeneratorComputer generator_computer(pool);
	return std::visit(generator_computer, generator);
}
