#ifndef __LETTER_HANDLER_CLASS__
#define __LETTER_HANDLER_CLASS__

#include "BaseHandler.hpp"
#include "../entity/movement/LetterMovement.hpp"

class BeatEvent;

class LetterHandler : public BaseHandler {
	public:
		LetterHandler(char letter);
		void update(const essentia::Pool& pool);
		USE_BASE_OP;
	private:
		LetterMovement _letter_movement;
};

#endif
