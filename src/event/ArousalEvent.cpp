#include "ArousalEvent.hpp"

ArousalEvent::ArousalEvent(float value)
	: _value(value)
{}

float ArousalEvent::get_value() const
{
	return _value;
}
