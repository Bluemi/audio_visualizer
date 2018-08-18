#include "TickDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

TickDataGenerator::TickDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, float min_amplitude)
	: _pool(pool), _algorithm_factory(algorithm_factory), _min_amplitude(min_amplitude)
{}

void TickDataGenerator::compute()
{
	std::cout << "Generating Tick Events... " << std::flush;

	essentia::standard::Algorithm* rhythm_extractor = _algorithm_factory->create("RhythmExtractor");
	rhythm_extractor->input("signal").set(_pool->value<std::vector<essentia::Real>>(data_identifier::AUDIO));

	std::vector<essentia::Real> ticks;
	essentia::Real bpm;
	std::vector<essentia::Real> estimates;
	std::vector<essentia::Real> bpmIntervals;

	rhythm_extractor->output("bpm").set(bpm);
	rhythm_extractor->output("ticks").set(ticks);
	rhythm_extractor->output("estimates").set(estimates);
	rhythm_extractor->output("bpmIntervals").set(bpmIntervals);

	rhythm_extractor->compute();

	_pool->set(data_identifier::TICK_POSITIONS, ticks);

	delete rhythm_extractor;

	std::cout << "Done." << std::endl;
}
