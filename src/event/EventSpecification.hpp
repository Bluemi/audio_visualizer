#ifndef __EVENTSPECIFICATION_CLASS__
#define __EVENTSPECIFICATION_CLASS__

#include <string>
#include <variant>
#include <vector>

template<typename Specification>
class EventSpecificationOperators
{
	public:
		bool operator==(const Specification&) const { return true; }
		bool operator!=(const Specification&) const { return false; }
		bool operator<(const Specification&) const { return false; }
		bool operator>(const Specification&) const { return false; }
		bool operator<=(const Specification&) const { return true; }
		bool operator>=(const Specification&) const { return true; }
};

class BeatEventSpecification : public EventSpecificationOperators<BeatEventSpecification>
{
	public:
		BeatEventSpecification(const std::string& filename, float min_amplitude) : _filename(filename), _min_amplitude(min_amplitude) {}
		float get_min_amplitude() const { return _min_amplitude; }
		std::string get_filename() const { return _filename; }
	private:
		std::string _filename;
		float _min_amplitude;
};

class AudioEventSpecification : public EventSpecificationOperators<AudioEventSpecification>
{
	public:
		AudioEventSpecification(const std::string& filename) : _filename(filename) {}
		std::string get_filename() const { return _filename; }
	private:
		std::string _filename;
};

using EventSpecification = std::variant<AudioEventSpecification, BeatEventSpecification>;

std::vector<EventSpecification> get_dependencies(const EventSpecification& specification);

#endif
