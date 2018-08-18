#include <iostream>

#include "AudioVisualizer.hpp"

#include "handler/Handler.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		std::cout << "usage:\n" << argv[0] << " <audiofile>" << std::endl;
		return 1;
	}

	const std::string audio_filename = argv[1];

	AudioVisualizer::init();

	InformationBuilder information_builder(audio_filename);

	information_builder.with_events({
			BeatEventSpecification(),
			// ArousalEventSpecification(),
			// ValenceEventSpecification()
		});

	information_builder.with_data({
			ArousalDataSpecification(),
			ValenceDataSpecification(),
			PartsDataSpecification()
		});

	InformationContainer information_container = information_builder.build();

	AccelerationFieldHandler afh;
	afh.set_groups({"main1", "main2"});

	AudioVisualizer av;
	av.add_handlers({ /* BeatEventHandler(),*/ ColorHandler(0.1f, 0.03f), ValenceArousalDebugHandler(), afh, DragHandler(0.12f) });
	av.run(information_container, audio_filename);

	return 0;
}
