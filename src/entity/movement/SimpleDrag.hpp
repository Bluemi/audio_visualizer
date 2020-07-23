#ifndef __SIMPLEDRAG_CLASS__
#define __SIMPLEDRAG_CLASS__

#include "IMovement.hpp"

class SimpleDrag : public IMovementCloneable<SimpleDrag> {
	public:
		SimpleDrag(float drag);

		virtual void apply_force(Movable* movable) override;
	private:
		float _drag;
};

#endif
