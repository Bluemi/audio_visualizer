#ifndef __SIMPLECOLORDRAG_CLASS__
#define __SIMPLECOLORDRAG_CLASS__

#include "IMovement.hpp"

class SimpleColorDrag : public IMovementCloneable<SimpleColorDrag> {
	public:
		SimpleColorDrag(float drag);

		virtual void apply_force(Movable* movable) override;
	private:
		float _drag;
};

#endif
