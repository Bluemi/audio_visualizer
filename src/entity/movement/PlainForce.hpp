#ifndef __PLAINFORCE_CLASS__
#define __PLAINFORCE_CLASS__

#include <vector>

class Movable;

class PlainForce {
	public:
		PlainForce(float strength);

		void apply_force(std::vector<Movable>& movables);
		void set_strength(float strength);
	private:
		float _strength;
};

#endif
