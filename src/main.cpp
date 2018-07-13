#include <iostream>

#include "AudioVisualizer.hpp"

int main()
{
	AudioVisualizer::init();
	AudioVisualizer av;
	EventList el = av.generate_events();
	av.setup_objects();
	av.run(el);

	return 0;
}
