#ifndef __AUDIOVISUALIZER_CLASS__
#define __AUDIOVISUALIZER_CLASS__

#include <visualizer/Visualizer.hpp>

#include "EventListBuilder.hpp"

class AudioVisualizer
{
	public:
		static void init();

		AudioVisualizer();
		EventList generate_events();
		void setup_objects();
		void run();
	private:
		visualizer::Visualizer _visualizer;
		EventListBuilder _event_list_builder;
};

#endif
