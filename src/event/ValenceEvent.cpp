#include "ValenceEvent.hpp"

ValenceEvent::ValenceEvent(float value)
	: _value(value)
{}

float ValenceEvent::get_value() const {
	return _value;
}
