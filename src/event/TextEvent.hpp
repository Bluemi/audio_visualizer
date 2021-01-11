#ifndef __TEXT_EVENT_CLASS__
#define __TEXT_EVENT_CLASS__

#include <string>

class TextEvent {
	public:
		TextEvent(const std::string& text);
		const std::string& get_text() const;
	private:
		std::string _text;
};

#endif
