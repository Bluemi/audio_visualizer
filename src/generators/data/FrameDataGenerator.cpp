#include "FrameDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

FrameDataGenerator::FrameDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

void FrameDataGenerator::compute()
{
	unsigned int frame_size = 2048;
	unsigned int hop_size = 1024;

	essentia::standard::Algorithm* fc = _algorithm_factory->create("FrameCutter",
																   "frameSize", frame_size,
																   "hopSize", hop_size);

	std::vector<essentia::Real> frame;

	fc->input("signal").set(_pool->value<std::vector<essentia::Real>>(data_identifier::AUDIO));
	fc->output("frame").set(frame);

	std::cout << "Cutting Frames... " << std::flush;

	while (true)
	{
		fc->compute();
		if (!frame.size()) { break; }
		_pool->add(data_identifier::FRAMES, frame);
	}

	std::cout << "Done." << std::endl;

	delete fc;
}
