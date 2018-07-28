#include <iostream>

#include "AudioVisualizer.hpp"

int main()
{
	AudioVisualizer::init();
	AudioVisualizer av;

	InformationBuilder information_builder("input.wav");

	information_builder.with_events({
			BeatEventSpecification(),
			ArousalEventSpecification(),
			ValenceEventSpecification()
		});

	information_builder.with_data({
			ArousalDataSpecification(),
			ValenceDataSpecification()
		});

	InformationContainer information_container = information_builder.build();

	av.run(information_container);

	return 0;
}
