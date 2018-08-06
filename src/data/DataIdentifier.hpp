#ifndef __DATAIDENTIFIER_CLASS__
#define __DATAIDENTIFIER_CLASS__

#include <string>

namespace data_identifier
{
	const std::string AUDIO = "audio";
	const std::string FRAMES = "frames";
	const std::string WINDOWED_FRAMES = "windowed_frames";
	const std::string SPECTRUM = "spectrum";
	const std::string BARK_BANDS = "bark_bands";
	const std::string BARK_BANDS_DIFFERENCES = "bark_bands_differences";
	const std::string AROUSAL_TIMELINE = "arousal_timeline";
	const std::string AROUSAL_DIFFS = "arousal_diffs";
	const std::string TICK_POSITIONS = "tick_positions";
	const std::string SPECTRUM_PEAKS_FREQUENCIES = "spectrum_peaks_frequencies";
	const std::string SPECTRUM_PEAKS_MAGNITUDES = "spectrum_peaks_magnitudes";
	const std::string PITCH_CLASS_PROFILES = "pitch_class_profiles";
	const std::string CHORDS = "chords";
	const std::string CHORD_STRENGTHS = "chord_strengths";
	const std::string VALENCE_TIMELINE = "valence_timeline";
}

#endif
