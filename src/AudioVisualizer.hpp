#ifndef __AUDIOVISUALIZER_CLASS__
#define __AUDIOVISUALIZER_CLASS__

#include <visualizer/Visualizer.hpp>

#include "information/InformationBuilder.hpp"
#include "information/InformationContainer.hpp"
#include "handler/Handler.hpp"

class AudioVisualizer
{
	public:
		static void init();

		AudioVisualizer();
		void setup_objects(visualizer::Visualizer* visualizer);
		void run(const InformationContainer& information_container);

		void add_handlers(const HandlerList& handler_list);
	private:
		EventList get_current_events(const EventList& event_list, double current_time);
		void handle_events(const EventList& event_list, const essentia::Pool& pool);
		void setup_handlers(visualizer::Visualizer* visualizer);
		void set_handler_frame_counter(unsigned int frame_counter);

		unsigned int _event_index;
		HandlerList _handlers;
};

#endif
