#include "TextEvent.hpp"

TextEvent::TextEvent(const std::string& text)
	: _text(text), _exploding(false)
{}

TextEvent::TextEvent(const std::string& text, bool exploding)
	: _text(text), _exploding(exploding)
{}

const std::string& TextEvent::get_text() const {
	return _text;
}

bool TextEvent::is_exploding() const {
	return _exploding;
}
