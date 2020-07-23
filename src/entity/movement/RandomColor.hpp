#ifndef __RANDOMCOLOR_CLASS__
#define __RANDOMCOLOR_CLASS__

#include "../creation/VectorGenerator.hpp"
#include "IMovement.hpp"

class RandomColor : public IMovementCloneable<RandomColor> {
	public:
		RandomColor(const VectorGenerator& color_gen);

		virtual void apply_force(Movable* movable) override;
		virtual bool should_be_removed() const override;
	private:
		VectorGenerator _color_gen;
		bool _used;
};

#endif
