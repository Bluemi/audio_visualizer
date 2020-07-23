#ifndef __COLORDRAG_CLASS__
#define __COLORDRAG_CLASS__

#include <vector>

class Movable;

class ColorDrag {
	public:
		ColorDrag(float intensity);

		void apply_force(std::vector<Movable>& movables);
		void apply_force(Movable* movable);
	private:
		float _intensity;
};

#endif
