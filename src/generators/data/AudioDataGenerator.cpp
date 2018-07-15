#include "AudioDataGenerator.hpp"

AudioDataGenerator::AudioDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

unsigned int SAMPLERATE = 44100;

void AudioDataGenerator::compute()
{
	essentia::standard::Algorithm* audio_loader = _algorithm_factory->create("MonoLoader",
																			 "filename", _filename,
																			 "sampleRate", SAMPLERATE);

	std::vector<essentia::Real> audio_data;
	audio_loader->output("audio").set(audio_data);

	std::cout << "Loading Audio Data... " << std::flush;

	audio_loader->compute();

	_pool->set("lowlevel.audio", audio_data);

	std::cout << "Done." << std::endl;

	delete audio_loader;
}

void AudioDataGenerator::set_filename(const std::string& filename)
{
	_filename = filename;
}
