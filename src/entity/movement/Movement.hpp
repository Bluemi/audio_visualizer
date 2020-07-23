#ifndef __MOVEMENT_CLASS__
#define __MOVEMENT_CLASS__

class IMovement;
class Movable;

class Movement {
	public:
		Movement(IMovement* imovement);
		Movement(const Movement& movement);
		Movement& operator=(Movement movement);
		~Movement();

		void init(Movable* movable);
		void apply_force(Movable* moveable);
		bool should_be_removed() const;
	private:
		IMovement* _imovement;
};

#endif
