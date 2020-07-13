#include "WindowedFrameDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

WindowedFrameDataGenerator::WindowedFrameDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void WindowedFrameDataGenerator::compute() {
	std::cout << "Windowing Frames... " << std::flush;

	essentia::standard::Algorithm* windower = _algorithm_factory->create("Windowing",
																		 "type", "blackmanharris62");

	const std::vector<std::vector<essentia::Real>> frames = _pool->value<std::vector<std::vector<essentia::Real>>>(data_identifier::FRAMES);

	std::vector<essentia::Real> windowed_frame;

	windower->output("frame").set(windowed_frame);

	for (const std::vector<essentia::Real>& frame : frames) {
		windower->input("frame").set(frame);
		windower->compute();
		_pool->add(data_identifier::WINDOWED_FRAMES, windowed_frame);
	}

	delete windower;

	std::cout << "Done." << std::endl;
}
