#include <iostream>

#include "AudioVisualizer.hpp"

#include "handler/Handler.hpp"

int main()
{
	AudioVisualizer::init();
	AudioVisualizer av;

	InformationBuilder information_builder("input.wav");

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

	av.add_handlers({ BeatEventHandler(), ColorHandler(0.1f, 0.03f), ValenceArousalDebugHandler() });

	av.run(information_container);

	return 0;
}
