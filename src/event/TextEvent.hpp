#ifndef __TEXT_EVENT_CLASS__
#define __TEXT_EVENT_CLASS__

#include <string>

class TextEvent {
	public:
		TextEvent(const std::string& text);
		TextEvent(const std::string& text, bool exploding);
		const std::string& get_text() const;
		bool is_exploding() const;
	private:
		std::string _text;
		bool _exploding;
};

#endif
