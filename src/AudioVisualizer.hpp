#ifndef __AUDIOVISUALIZER_CLASS__
#define __AUDIOVISUALIZER_CLASS__

#include <visualizer/visualizer.hpp>
#include <visualizer/shape/shape_heap.hpp>

#include "information/InformationBuilder.hpp"
#include "information/InformationContainer.hpp"
#include "handler/Handler.hpp"
#include "handler/Compositor.hpp"

class AudioVisualizer {
	public:
		AudioVisualizer();
		void setup_objects(EntityBuffer* entity_buffer, visualizer::ShapeHeap& shape_heap);
		void run(const InformationContainer& information_container, const std::string& audio_filename);

		void add_handlers(const HandlerList& handler_list);
	private:
		EventList get_current_events(const EventList& event_list, double current_time);
		void handle_events(const EventList& event_list, const essentia::Pool& pool);
		void setup_handlers(EntityBuffer* entity_buffer);
		void set_handler_frame_counter(unsigned int frame_counter);

		unsigned int _event_index;
		HandlerList _handlers;
		Compositor _compositor;
};

#endif
