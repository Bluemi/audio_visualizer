#ifndef __IMOVEMENT_CLASS__
#define __IMOVEMENT_CLASS__

class Movable;

class IMovement {
	public:
		virtual ~IMovement();

		virtual void init(Movable* movable);
		virtual void apply_force(Movable* movable) = 0;
		virtual bool should_be_removed() const;

		virtual IMovement* clone() const = 0;
};

/*
 * Inspired by:
 * https://stackoverflow.com/questions/5731217/how-to-copy-create-derived-class-instance-from-a-pointer-to-a-polymorphic-base-c
 */

template<typename SubMovement>
class IMovementCloneable : public IMovement {
	public:
		virtual IMovement* clone() const override {
			return new SubMovement(static_cast<const SubMovement&>(*this));
		}
};

#endif
