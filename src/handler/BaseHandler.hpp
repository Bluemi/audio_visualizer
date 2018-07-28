#ifndef __BASEHANDLER_CLASS__
#define __BASEHANDLER_CLASS__

#include <visualizer/Visualizer.hpp>

namespace essentia { class Pool; }

class BaseHandler
{
	public:
		void set_visualizer(visualizer::Visualizer* visualizer) { _visualizer = visualizer; }
		void set_frame_counter(unsigned int frame_counter) { _frame_counter = frame_counter; }

		template<typename EventType>
		void operator()(const EventType&) {}

		void update(const essentia::Pool&) {}
	protected:
		visualizer::Visualizer* _visualizer;
		unsigned int _frame_counter;
};

#define USE_BASE_OP using BaseHandler::operator();

#endif