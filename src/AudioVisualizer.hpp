#ifndef __AUDIOVISUALIZER_CLASS__
#define __AUDIOVISUALIZER_CLASS__

#include <visualizer/visualizer.hpp>

#include "information/InformationBuilder.hpp"
#include "information/InformationContainer.hpp"
#include "handler/Handler.hpp"
#include "handler/Compositor.hpp"

namespace visualizer { class ShapeHeap; }

class AudioVisualizer {
	public:
		AudioVisualizer();
		void setup_objects(EntityBuffer* entity_buffer, visualizer::ShapeHeap& shape_heap);
		void run(const InformationContainer& information_container, const std::string& audio_filename, bool interactive);
		void take_screenshot(GLFWwindow* window, unsigned int tick_counter, int screen_width, int screen_height);

		void add_handlers(const HandlerList& handler_list);
	private:
		EventList get_current_events(const EventList& event_list, double current_time);
		void handle_events(const EventList& event_list, const essentia::Pool& pool);
		void setup_handlers(EntityBuffer* entity_buffer, visualizer::ShapeHeap& shape_heap);
		void set_handler_frame_counter(unsigned int frame_counter);

		unsigned int _event_index;
		HandlerList _handlers;
		Compositor _compositor;
};

#endif
