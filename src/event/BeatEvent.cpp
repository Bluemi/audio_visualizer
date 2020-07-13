#include "BeatEvent.hpp"

BeatEvent::BeatEvent(float relative_amplitude)
	: _relative_amplitude(relative_amplitude)
{}

float BeatEvent::get_relative_amplitude() const {
	return _relative_amplitude;
}
