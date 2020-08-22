#ifndef __LETTER_HANDLER_CLASS__
#define __LETTER_HANDLER_CLASS__

#include "BaseHandler.hpp"
#include "../entity/movement/LetterMovement.hpp"

class BeatEvent;

class LetterHandler : public BaseHandler {
	public:
		LetterHandler(char letter);
		void init(visualizer::ShapeHeap& shape_heap);
		void update(const essentia::Pool& pool);
		USE_BASE_OP;

		void set_position(const glm::vec3& position);
		void set_scale(float scale);
	private:
		LetterMovement _letter_movement;
		char _letter;
};

#endif
