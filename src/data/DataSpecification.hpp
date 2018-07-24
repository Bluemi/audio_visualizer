#ifndef __DATASPECIFICATION_CLASS__
#define __DATASPECIFICATION_CLASS__

#include <string>
#include <variant>
#include <vector>

template<typename Specification>
class DataSpecificationOperators
{
	public:
		bool operator==(const Specification&) const { return true; }
		bool operator!=(const Specification&) const { return false; }
		bool operator<(const Specification&) const { return false; }
		bool operator>(const Specification&) const { return false; }
		bool operator<=(const Specification&) const { return true; }
		bool operator>=(const Specification&) const { return true; }
};

class AudioDataSpecification : public DataSpecificationOperators<AudioDataSpecification> {};
class FrameDataSpecification : public DataSpecificationOperators<FrameDataSpecification> {};
class WindowedFrameDataSpecification : public DataSpecificationOperators<WindowedFrameDataSpecification> {};
class SpectrumDataSpecification : public DataSpecificationOperators<SpectrumDataSpecification> {};
class BarkBandsDataSpecification : public DataSpecificationOperators<BarkBandsDataSpecification> {};
class BarkBandsDifferenceDataSpecification : public DataSpecificationOperators<BarkBandsDifferenceDataSpecification> {};

class WriteDataSpecification : public DataSpecificationOperators<WriteDataSpecification>
{
	public:
		WriteDataSpecification(const std::string& output_filename) : _output_filename(output_filename) {}
		std::string get_output_filename() const { return _output_filename; }
		void set_output_filename(const std::string& output_filename) { _output_filename = output_filename; }
	private:
		std::string _output_filename;
};

class TickDataSpecification : public DataSpecificationOperators<TickDataSpecification>
{
	public:
		TickDataSpecification(float min_amplitude) : _min_amplitude(min_amplitude) {}
		float get_min_amplitude() const { return _min_amplitude; }
	private:
		float _min_amplitude;
};

using DataSpecification = std::variant<AudioDataSpecification,
									   FrameDataSpecification,
									   WindowedFrameDataSpecification,
									   SpectrumDataSpecification,
									   BarkBandsDataSpecification,
									   BarkBandsDifferenceDataSpecification,
									   TickDataSpecification,
									   WriteDataSpecification>;

std::vector<DataSpecification> get_dependencies(const DataSpecification& specification);

#endif
