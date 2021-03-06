#include "DataSpecification.hpp"

struct {
	std::vector<DataSpecification> operator()(const AudioDataSpecification&) {
		return {};
	}

	std::vector<DataSpecification> operator()(const FrameDataSpecification&) {
		return { AudioDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const WindowedFrameDataSpecification&) {
		return { FrameDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const SpectrumDataSpecification&) {
		return { WindowedFrameDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const BarkBandsDataSpecification&) {
		return { SpectrumDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const BarkBandsDifferenceDataSpecification&) {
		return { BarkBandsDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const SpectrumPeakDataSpecification&) {
		return { SpectrumDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const PitchClassProfileDataSpecification&) {
		return { SpectrumPeakDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const ChordDataSpecification&) {
		return { PitchClassProfileDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const ArousalDataSpecification&) {
		return { BarkBandsDifferenceDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const ValenceDataSpecification&) {
		return { ChordDataSpecification(), PitchClassProfileDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const PartsDataSpecification&) {
		return { ArousalDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const TickDataSpecification&) {
		return { AudioDataSpecification() };
	}

	std::vector<DataSpecification> operator()(const WriteDataSpecification&) {
		return { TickDataSpecification(0.f) };
	}
} _dependency_resolver;

std::vector<DataSpecification> get_dependencies(const DataSpecification& specification) {
	return std::visit(_dependency_resolver, specification);
}
