#include <iostream>

#include "AudioVisualizer.hpp"

int main()
{
	AudioVisualizer::init();
	AudioVisualizer av;
	InformationContainer info = av.generate_information();
	av.run(info);

	return 0;
}
