#include "Movement.hpp"

#include <algorithm>

#include "IMovement.hpp"

Movement::Movement(IMovement* imovement)
	: _imovement(imovement)
{}

Movement::Movement(const Movement& movement) {
	_imovement = movement._imovement->clone();
}

Movement& Movement::operator=(Movement movement) {
	std::swap(_imovement, movement._imovement);
	return *this;
}

Movement::~Movement() {
	delete _imovement;
}

void Movement::init(Movable* movable) {
	_imovement->init(movable);
}

void Movement::apply_force(Movable* moveable) {
	_imovement->apply_force(moveable);
}

bool Movement::should_be_removed() const {
	return _imovement->should_be_removed();
}
