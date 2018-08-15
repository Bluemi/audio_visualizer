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

	AccelerationFieldHandler afh;
	afh.set_groups({"main1", "main2"});
	av.add_handlers({ /*BeatEventHandler(),*/ ColorHandler(0.1f, 0.03f), ValenceArousalDebugHandler(), afh, DragHandler(0.12f) });

	av.run(information_container);

	return 0;
}
