#include <iostream>

#include "AudioVisualizer.hpp"

int main()
{
	AudioVisualizer::init();
	AudioVisualizer av;
	av.generate_events();
	av.setup_objects();
	av.run();

	return 0;
}
