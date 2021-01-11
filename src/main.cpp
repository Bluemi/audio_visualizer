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
		.with_events({
			BeatEventSpecification(),
			TextEventSpecification({
				{2.7f, "Suzys Gone"},
				{6.7f, "Suzys Gone  -  Azure Raids"},
				{10.7f, ""},
				{14.5f, "Hey lil' Suzy, hope you're doin' fine."},
				{18.5f, "You go your way, and I’ll go mine."},
				{22.3f, "When you left, you didn’t tell me,"},
				{26.0f, "What happened to us, why can’t we be?"},
				{29.0f, "Was it me?"},
				{30.8f, "Was it me? Am I"},
				{32.4f, "Was it me? Am I the one to blame?"},
				{36.5f, "Ohh Suzy"},
				{37.7f, "Ohh Suzy, will you ever"},
				{39.5f, "Ohh Suzy, will you ever come back again?"},
				{43.5f, "Was it me?"},
				{45.3f, "Was it me? Am I"},
				{47.1f, "Was it me? Am I the one to blame?"},
				{50.5f, "Ohh Suzy"},
				{52.3f, "Ohh Suzy, will you ever"},
				{54.2f, "Ohh Suzy, will you ever come back again?"},
				{58.5f, ""},
				{101.0f, "This love has seen better days"},
				{104.8f, "but my love won't ever fade away."},
				{108.5f, "You kept in mind I hate good-bye's."},
				{112.0f, "Without a word you went outta my life."},
				{114.8f, "Was it me?"},
				{116.5f, "Was it me? Am I"},
				{118.5f, "Was it me? Am I the one to blame?"},
				{122.5f, "Ohh Suzy"},
				{123.6f, "Ohh Suzy, will you ever"},
				{125.8f, "Ohh Suzy, will you ever come back again?"},
				{130.0f, "Was it me?"},
				{132.0f, "Was it mee?"},
				{133.0f, "Was it meee?"},
				{137.0f, "Ohh Suzy"},
				{138.7f, "Ohh Suzy, will you ever"},
				{140.2f, "Ohh Suzy, will you ever come back again?"},
				{144.8f, ""},
				{158.0f, "Was it me?"},
				{160.0f, "Was it me? Am I"},
				{162.0f, "Was it me? Am I the one to blame?"},
				{166.0f, "Ohh Suzy"},
				{167.0f, "Ohh Suzy, will you ever"},
				{169.0f, "Ohh Suzy, will you ever come back again?"},
				{172.5f, "Was it me?"},
				{174.5f, "Was it mee?"},
				{176.0f, "Was it meee?"},
				{180.0f, "Ohh Suzy"},
				{187.5f, "Suzys Gone  - Azure Raids"},
			})
		})
		.with_data({ ArousalDataSpecification(), ValenceDataSpecification(), PartsDataSpecification() });

	std::optional<InformationContainer> information_container = information_builder.build();

	if (information_container) {
		AudioVisualizer av;

		av.add_handlers({ ColorHandler(0.1f, 0.03f), DragHandler(0.12f) });
		// av.add_handlers({ ValenceArousalDebugHandler() });
		// av.add_handlers({ AccelerationFieldHandler() });
		av.add_handlers({ BeatEventHandler() });

		// AccelerationFieldHandler afh;
		// afh.groups = { "main1" };

		// av.add_handlers({ afh });

		// av.add_handlers(to_handler_list(create_string_handlers("Suzy's Gone", glm::vec3(0.f), 10.f)));
		// av.add_handlers(to_handler_list(create_string_handlers("Azure Raids", glm::vec3(0.f, -5.f, 5.f), 5.f)));
		av.add_handlers({ TextHandler(40) });

		av.run(*information_container, audio_filename, false);
	}

	return 0;
}
