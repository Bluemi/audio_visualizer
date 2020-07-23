#include "IMovement.hpp"

IMovement::~IMovement() {}

void IMovement::init(Movable*)
{}

bool IMovement::should_be_removed() const {
	return false;
}
