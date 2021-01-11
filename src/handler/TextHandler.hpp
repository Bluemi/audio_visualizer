#ifndef __TEXT_HANDLER_CLASS__
#define __TEXT_HANDLER_CLASS__

#include "BaseHandler.hpp"

class TextEvent;

class TextHandler : public BaseHandler {
	public:
		TextHandler(int max_letters);
		void init(visualizer::ShapeHeap& shape_heap);
		void update(const essentia::Pool& pool);
		void operator()(const TextEvent& text_event);
		USE_BASE_OP;
	private:
		int _max_letters;
		std::string _current_text;
		bool _initialized;
};

#endif
