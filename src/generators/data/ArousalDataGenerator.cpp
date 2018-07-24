#include "ArousalDataGenerator.hpp"

#include "../../misc/Misc.hpp"
#include "../../data/DataIdentifier.hpp"
#include <visualizer/misc/Math.hpp>

ArousalDataGenerator::ArousalDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

std::vector<float> calculate_loudness_time_line(const misc::Matrix& bark_bands_differences)
{
	std::vector<float> loudness_time_line;
	const unsigned int num_frames = bark_bands_differences[0].size();

	for (unsigned int time_index = 0; time_index < num_frames; time_index++)
	{
		float loudness_change = 0.f;
		for (unsigned int frequency_index = 0; frequency_index < bark_bands_differences.size(); frequency_index++)
		{
			loudness_change += std::abs(bark_bands_differences[frequency_index][time_index]);
		}
		loudness_time_line.push_back(loudness_change);
	}

	return loudness_time_line;
}

const float LOUDNESS_LIMIT_RATE = 0.5f;
const float ACCELERATION_LIMIT = 0.15f;
const float ACCELERATION = 0.02f;

/*
std::vector<float> calculate_arousal(std::vector<float> loudness_time_line)
{
	float max_loudness = 0.f;
	double sum = 0.f;

	for (float loudness : loudness_time_line)
	{
		sum += loudness;
		if (loudness > max_loudness)
		{
			max_loudness = loudness;
		}
	}

	float avg_loudness = sum / loudness_time_line.size();
	if (avg_loudness < 0.00001f)
		avg_loudness = 1.f;

	if (max_loudness < 0.00001f)
		max_loudness = 1.f;

	std::vector<float> arousal_timeline;
	float arousal = 0.f;

	std::cout << "avg_loudness: " << avg_loudness << std::endl;
	std::cout << "max_loudness: " << max_loudness << std::endl;

	for (float loudness : loudness_time_line)
	{
		loudness = loudness / avg_loudness;

		if (loudness < 1.f)
			loudness = 0.f;
		else
			loudness = std::pow(loudness, 1.0/2.0);

		float arousal_acceleration = (loudness - arousal) * ACCELERATION;
		arousal += arousal_acceleration;

		arousal_timeline.push_back(arousal);
	}

	return arousal_timeline;
}
*/

std::vector<float> calc_arousal(const std::vector<float>& time_line)
{
	float x = 0.f;
	float max = 0.f;

	std::vector<float> arousals;

	for (float loudness_change : time_line)
	{
		x = x*0.98f;
		if (x < loudness_change)
		{
			x = loudness_change;
		}

		/*
		std::cout << "loudness_change: " << loudness_change << std::endl;
		std::cout << "x: " << x << std::endl;
		*/

		float arousal = 0.f;
		if (loudness_change > 0.f)
			arousal = loudness_change;
		else
			arousal = x * -loudness_change * 20.f;
		
		if (max < arousal)
		{
			max = arousal;
		}
		arousals.push_back(arousal);
	}

	return arousals;
}

const float MIN_LOUDNESS = 0.2f;

std::vector<float> calculate_arousal(misc::Matrix bark_bands_differences)
{
	double sum = 0.0;
	float max_loudness_change = 0.f;
	for (const std::vector<float>& time_line : bark_bands_differences)
		for (float loudness_change : time_line)
		{
			sum += std::abs(loudness_change);
			max_loudness_change = std::max(max_loudness_change, loudness_change);
		}

	float avg_loudness_change = sum / (bark_bands_differences.size() * bark_bands_differences[0].size());
	std::cout << "avg_loudness_change: " << avg_loudness_change << std::endl;
	std::cout << "max_loudness_change: " << max_loudness_change << std::endl;

	max_loudness_change = std::max(max_loudness_change, MIN_LOUDNESS);

	for (std::vector<float>& time_line : bark_bands_differences)
		for (float& loudness_change : time_line)
			loudness_change = loudness_change / max_loudness_change;

	std::vector<float> merged_arousals;

	for (const std::vector<float>& time_line : bark_bands_differences)
	{
		std::vector<float> arousal = calc_arousal(time_line);
		if (merged_arousals.size() == 0)
		{
			merged_arousals = arousal;
		} else {
			for (unsigned int i = 0; i < merged_arousals.size(); i++)
			{
				merged_arousals[i] += arousal[i];
			}
		}
	}

	for (float& f : merged_arousals)
	{
		f = std::sqrt(f);
	}

	return merged_arousals;
}

void ArousalDataGenerator::compute()
{
	std::cout << "Calculating Arousal Data... " << std::flush;

	misc::Matrix bark_bands_differences = _pool->value<misc::Matrix>(data_identifier::BARK_BANDS_DIFFERENCES);
	// std::vector<float> loudness_time_line = calculate_loudness_time_line(bark_bands_differences);
	std::vector<float> arousal_timeline = calculate_arousal(bark_bands_differences);

	_pool->set(data_identifier::AROUSAL_TIMELINE, arousal_timeline);

	std::cout << "Done." << std::endl;
}
