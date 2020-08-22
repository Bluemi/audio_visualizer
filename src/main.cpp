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

		av.add_handlers({ LetterHandler('M') });

		LetterHandler b_handler('o');
		b_handler.set_position(glm::vec3(0.f, 0.f, 5.f));
		av.add_handlers({ b_handler });

		LetterHandler c_handler('n');
		c_handler.set_position(glm::vec3(0.f, 0.f, 10.f));
		av.add_handlers({ c_handler });

		LetterHandler d_handler('a');
		d_handler.set_position(glm::vec3(0.f, 0.f, 15.f));
		av.add_handlers({ d_handler });

		av.run(*information_container, audio_filename);

	}

	return 0;
}
