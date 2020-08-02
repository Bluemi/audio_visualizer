#include <iostream>

#include "AudioVisualizer.hpp"
#include "handler/Handler.hpp"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "usage:\n" << argv[0] << " <audiofile>" << std::endl;
		return 1;
	}

	const std::string audio_filename = argv[1];

	InformationBuilder information_builder(audio_filename);

	information_builder
		.with_events({ BeatEventSpecification() })
		.with_data({ ArousalDataSpecification(), ValenceDataSpecification(), PartsDataSpecification() });

	std::optional<InformationContainer> information_container = information_builder.build();

	if (information_container) {
		AudioVisualizer av;

		av.add_handlers({ ColorHandler(0.1f, 0.03f), DragHandler(0.12f) });
		// av.add_handlers({ ValenceArousalDebugHandler() });
		// av.add_handlers({ AccelerationFieldHandler() });
		av.add_handlers({ BeatEventHandler() });

		av.add_handlers({ LetterHandler('A') });
		av.add_handlers({ LetterHandler('B') });

		av.run(*information_container, audio_filename);

	}

	return 0;
}
