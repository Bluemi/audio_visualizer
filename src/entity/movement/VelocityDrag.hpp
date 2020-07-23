#ifndef __VELOCITYDRAG_CLASS__
#define __VELOCITYDRAG_CLASS__

#include <vector>

class Movable;

class VelocityDrag {
	public:
		VelocityDrag(float intensity);

		void apply_force(std::vector<Movable>& movables);
		void apply_force(Movable* movable);
	private:
		float _intensity;
};

#endif
