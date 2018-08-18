#include "AudioDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"

AudioDataGenerator::AudioDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

unsigned int SAMPLERATE = 44100;

void AudioDataGenerator::compute()
{
	std::cout << "Loading Audio Data... " << std::flush;

	essentia::standard::Algorithm* audio_loader = _algorithm_factory->create("MonoLoader",
																			 "filename", _filename,
																			 "sampleRate", SAMPLERATE);

	std::vector<essentia::Real> audio_data;
	audio_loader->output("audio").set(audio_data);

	audio_loader->compute();

	_pool->set(data_identifier::AUDIO, audio_data);

	delete audio_loader;

	std::cout << "Done." << std::endl;
}

void AudioDataGenerator::set_filename(const std::string& filename)
{
	_filename = filename;
}
