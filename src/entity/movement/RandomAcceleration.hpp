#ifndef __RANDOMACCELERATION_CLASS__
#define __RANDOMACCELERATION_CLASS__

#include "IMovement.hpp"

class Movable;

class RandomAcceleration : public IMovementCloneable<RandomAcceleration> {
	public:
		RandomAcceleration(float intensity);

		virtual void apply_force(Movable* movable) override;
		virtual bool should_be_removed() const override;
	private:
		float _intensity;
		bool _should_be_removed;
};

#endif
