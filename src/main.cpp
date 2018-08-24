#include <iostream>

#include "AudioVisualizer.hpp"
#include "handler/Handler.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "usage:\n" << argv[0] << " <audiofile>" << std::endl;
		std::cout << argc << std::endl;
		return 1;
	}

	const std::string audio_filename = argv[1];

	AudioVisualizer::init();

	InformationBuilder information_builder(audio_filename);

	information_builder
		.with_events({ BeatEventSpecification() })
		.with_data({ ArousalDataSpecification(), ValenceDataSpecification(), PartsDataSpecification() });

	std::optional<InformationContainer> information_container = information_builder.build();

	if (information_container)
	{
		AccelerationFieldHandler afh;
		afh.set_groups({"main1", "main2"});

		AudioVisualizer av;
		av.add_handlers({ ColorHandler(0.1f, 0.03f), ValenceArousalDebugHandler(), afh, DragHandler(0.12f) });
		av.run(*information_container, audio_filename);
	}

	return 0;
}
