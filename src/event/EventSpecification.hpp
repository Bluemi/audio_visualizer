#ifndef __EVENTSPECIFICATION_CLASS__
#define __EVENTSPECIFICATION_CLASS__

#include <variant>
#include <tuple>

#include "../data/DataSpecification.hpp"

class TickEventSpecification {
	public:
		TickEventSpecification(float min_amplitude) : _min_amplitude(min_amplitude) {}
		float get_min_amplitude() const { return _min_amplitude; }
	private:
		float _min_amplitude;
};

class BeatEventSpecification {};
class ArousalEventSpecification {};
class ValenceEventSpecification {};

class TextEventSpecification {
	public:
		TextEventSpecification(const std::vector<std::tuple<float, std::string>>& texts) : _texts(texts) {}
		const std::vector<std::tuple<float, std::string>>& get_texts() const {
			return _texts;
		}
	private:
		std::vector<std::tuple<float, std::string>> _texts;
};

using EventSpecification = std::variant<TickEventSpecification, BeatEventSpecification, ArousalEventSpecification, ValenceEventSpecification, TextEventSpecification>;

std::vector<DataSpecification> get_needed_data_specifications(const EventSpecification& event_specification);

#endif
