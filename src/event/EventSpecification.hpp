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

class BeatEventSpecification {
	public:
		BeatEventSpecification() : _accelerations() {}
		BeatEventSpecification(const std::vector<std::tuple<float, float>>& accelerations) : _accelerations(accelerations) {}
		std::vector<std::tuple<float, float>> _accelerations;
};

class ArousalEventSpecification {};
class ValenceEventSpecification {};

class TextEventSpecification {
	public:
		TextEventSpecification(const std::vector<std::tuple<float, std::string, bool>>& texts) : _texts(texts) {}
		const std::vector<std::tuple<float, std::string, bool>>& get_texts() const {
			return _texts;
		}
	private:
		std::vector<std::tuple<float, std::string, bool>> _texts;
};

class ImageEventSpecification {
	public:
		ImageEventSpecification(int image_id, float start_time, float end_time) : image_id(image_id), start_time(start_time), end_time(end_time) {}
		int image_id;
		float start_time;
		float end_time;
};

using EventSpecification = std::variant<TickEventSpecification, BeatEventSpecification, ArousalEventSpecification, ValenceEventSpecification, TextEventSpecification, ImageEventSpecification>;

std::vector<DataSpecification> get_needed_data_specifications(const EventSpecification& event_specification);

#endif
