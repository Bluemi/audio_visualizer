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
		void run(const EventList& event_list);
	private:
		EventList get_current_events(const EventList& event_list);

		visualizer::Visualizer _visualizer;
		unsigned int _event_index;
};

#endif
