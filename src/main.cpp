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
				{2.7f, "       Suzys Gone", false},
				{6.7f, "       Suzys Gone  -  Azure Raids", false},
				{10.7f, "", false},
				{14.5f, "Hey, lil' Suzy, hope you're doin' fine.", false},
				{18.5f, "You go your way, and I'll go mine.", false},
				{22.3f, "When you left, you didn't tell me,", false},
				{26.0f, "What happened to us, why can't we be?", false},
				{29.0f, "Was it me?", true},
				{30.8f, "Was it me? Am I", false},
				{32.4f, "Was it me? Am I the one to blame?", false},
				{36.5f, "Ohh Suzy", false},
				{37.7f, "Ohh Suzy, will you ever", false},
				{39.5f, "Ohh Suzy, will you ever come back again?", false},
				{43.5f, "Was it me?", false},
				{45.3f, "Was it me? Am I", false},
				{47.1f, "Was it me? Am I the one to blame?", false},
				{50.5f, "Ohh Suzy", false},
				{52.3f, "Ohh Suzy, will you ever", false},
				{54.2f, "Ohh Suzy, will you ever come back again?", false},
				{58.5f, "", true},
				{101.0f, "This love has seen better days,", false},
				{104.8f, "but my love won't ever fade away.", false},
				{108.5f, "You kept in mind I hate goodbye's.", false},
				{112.0f, "Without a word you went outta my life.", false},
				{114.8f, "Was it me?", true},
				{116.5f, "Was it me? Am I", false},
				{118.5f, "Was it me? Am I the one to blame?", false},
				{122.5f, "Ohh Suzy", false},
				{123.6f, "Ohh Suzy, will you ever", false},
				{125.8f, "Ohh Suzy, will you ever come back again?", false},
				{130.0f, "Was it me?", false},
				{132.0f, "Was it mee?", false},
				{133.0f, "Was it meee?", false},
				{137.0f, "Ohh Suzy", false},
				{138.7f, "Ohh Suzy, will you ever", false},
				{140.2f, "Ohh Suzy, will you ever come back again?", false},
				{144.8f, "", true},
				{158.0f, "Was it me?", true},
				{160.0f, "Was it me? Am I", false},
				{162.0f, "Was it me? Am I the one to blame?", false},
				{166.0f, "Ohh Suzy", false},
				{167.0f, "Ohh Suzy, will you ever", false},
				{169.0f, "Ohh Suzy, will you ever come back again?", false},
				{172.5f, "Was it me?", false},
				{174.5f, "Was it mee?", false},
				{176.0f, "Was it meee?", false},
				{180.0f, "                 Ohh Suzy", true},
				{189.5f, "       Suzys Gone  -  Azure Raids", true},
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

		av.run(*information_container, audio_filename, true);
	}

	return 0;
}
