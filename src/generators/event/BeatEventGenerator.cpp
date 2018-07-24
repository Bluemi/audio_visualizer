#include "BeatEventGenerator.hpp"

#include <algorithm>

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"
#include "../../misc/Misc.hpp"

class Threshold
{
	public:
		Threshold(double decay, double reset_rate)
			: _f(0.0), _decay(decay), _reset_rate(reset_rate)
		{}

		void update(double value)
		{
			_f *= _decay;
			double f = _reset_rate * value;
			if (_f < f)
				_f = f;
		}
		bool undercut(double f) { return _f < f; }

	private:
		double _f;
		double _decay;
		double _reset_rate;
};

struct BeatPosition
{
	BeatPosition(float v, unsigned int p, unsigned int f)
		: value(v), position(p), frequency_band_index(f)
	{}

	float value;
	unsigned int position;
	unsigned int frequency_band_index;

	bool operator==(const BeatPosition& b) const
	{
		return (position == b.position) && (frequency_band_index == b.frequency_band_index);
	}

	bool operator<(const BeatPosition& b) const
	{
		return position < b.position;
	}
};

std::vector<BeatPosition> get_event_positions(const std::vector<float>& time_line)
{
	std::vector<BeatPosition> positions;
	Threshold threshold(0.97, 1.5);
	unsigned int position = 0;
	for (float f : time_line)
	{
		if (threshold.undercut(f))
		{
			positions.push_back(BeatPosition(f, position, 0));
		}
		threshold.update(f);
		position++;
	}

	return positions;
}

BeatPosition group_positions(const std::vector<BeatPosition>& position_group)
{
	if (!position_group.size())
	{
		std::cout << "position_group with size 0 detected" << std::endl;
		return BeatPosition(0, 0, 0);
	}
	unsigned int position = position_group[0].position;
	float value = 0.f;

	for (const BeatPosition& pos : position_group)
	{
		if (pos.position < position)
			position = pos.position;
		value += pos.value;
	}

	return BeatPosition(value, position, 0);
}

const unsigned int MIN_POSITION_DIFFERENCE = 1;

std::vector<BeatPosition> filter_positions(std::vector<BeatPosition> positions)
{
	std::sort(positions.begin(), positions.end());

	std::vector<BeatPosition> filtered_positions;

	std::vector<BeatPosition> local_group;

	for (auto iter = positions.cbegin(); iter != positions.cend(); ++iter)
	{
		local_group.push_back(*iter);

		if ((iter+1) != positions.cend())
		{
			if ((iter+1)->position - iter->position > MIN_POSITION_DIFFERENCE)
			{
				filtered_positions.push_back(group_positions(local_group));
				local_group.clear();
			}
		}
	}
	filtered_positions.push_back(group_positions(local_group));

	return filtered_positions;
}

EventList BeatEventGenerator::compute(const essentia::Pool& pool) const
{
	std::vector<std::vector<float>> changes = pool.value<std::vector<std::vector<essentia::Real>>>(data_identifier::BARK_BANDS_DIFFERENCES);

	std::vector<BeatPosition> positions;

	for (const std::vector<float>& time_line : changes)
	{
		std::vector<BeatPosition> new_positions = get_event_positions(time_line);
		// append new positions
		positions.insert(positions.end(), new_positions.cbegin(), new_positions.cend());
	}

	std::vector<BeatPosition> filtered_positions = filter_positions(positions);

	EventList event_list;

	for (const BeatPosition& pos : filtered_positions)
	// for (const BeatPosition& pos : positions)
	{
		Event e(BeatEvent(pos.value), pos.position*(1024.f / 44100.f));
		event_list.push_back(e);
	}

	return event_list;
}
