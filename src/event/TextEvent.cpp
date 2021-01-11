#include "TextEvent.hpp"

TextEvent::TextEvent(const std::string& text)
	: _text(text)
{}

const std::string& TextEvent::get_text() const {
	return _text;
}
