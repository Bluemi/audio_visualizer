#ifndef __AUDIOVISUALIZER_CLASS__
#define __AUDIOVISUALIZER_CLASS__

#include <visualizer/Visualizer.hpp>

#include "InformationBuilder.hpp"

class AudioVisualizer
{
	public:
		static void init();

		AudioVisualizer();
		EventList generate_events();
		void setup_objects(visualizer::Visualizer* visualizer);
		void run(const EventList& event_list);
	private:
		EventList get_current_events(const EventList& event_list, double current_time);
		void handle_events(const EventList& event_list, visualizer::Visualizer* visualizer);

		unsigned int _event_index;
};

#endif
