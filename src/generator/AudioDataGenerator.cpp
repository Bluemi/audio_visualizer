#include "AudioDataGenerator.hpp"

AudioDataGenerator::AudioDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory, const std::string& filename)
	: _pool(pool), _algorithm_factory(algorithm_factory), _filename(filename)
{}

unsigned int SAMPLERATE = 44100;

void AudioDataGenerator::compute()
{
	essentia::standard::Algorithm* audio_loader = _algorithm_factory->create("MonoLoader",
																			 "filename", _filename,
																			 "sampleRate", SAMPLERATE);

	std::vector<essentia::Real> audio_data;
	audio_loader->output("audio").set(audio_data);
	audio_loader->compute();
	_pool->set("lowlevel.audio", audio_data);

	delete audio_loader;
}
