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

		LetterHandler handler1('A');
		handler1.set_position(glm::vec3(0.f, 0.f, 0.f));
		av.add_handlers({ handler1 });

		LetterHandler handler2('z');
		handler2.set_position(glm::vec3(0.f, 0.f, 5.f));
		av.add_handlers({ handler2 });

		LetterHandler handler3('u');
		handler3.set_position(glm::vec3(0.f, 0.f, 10.f));
		av.add_handlers({ handler3 });

		LetterHandler handler4('r');
		handler4.set_position(glm::vec3(0.f, 0.f, 15.f));
		av.add_handlers({ handler4 });

		LetterHandler handler5('e');
		handler5.set_position(glm::vec3(0.f, 0.f, 20.f));
		av.add_handlers({ handler5 });

		av.run(*information_container, audio_filename);

	}

	return 0;
}
