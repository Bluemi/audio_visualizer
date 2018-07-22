#include "BeatEventGenerator.hpp"

#include <essentia/pool.h>

#include "../../data/DataIdentifier.hpp"
#include "../../misc/Misc.hpp"

std::vector<std::vector<float>> spin(const std::vector<std::vector<essentia::Real>>& vec)
{
	std::vector<std::vector<float>> spinned(vec[0].size());

	for (std::vector<float>& v : spinned)
	{
		v = std::vector<float>(vec.size());
	}

	for (unsigned int band_index = 0; band_index < vec.size(); band_index++)
	{
		for (unsigned int f_index = 0; f_index < vec[band_index].size(); f_index++)
		{
			spinned[f_index][band_index] = vec[band_index][f_index];
		}
	}

	return spinned;
}

std::vector<std::vector<float>> calculate_changes(const std::vector<std::vector<essentia::Real>>& bark_bands)
{
	std::vector<std::vector<float>> spinned = spin(bark_bands);
	std::vector<std::vector<float>> changes;

	for (const std::vector<float>& time_line : spinned)
	{
		std::vector<float> time_line_changes { 0.f };
		for (unsigned int i = 1; i < time_line.size(); i++)
		{
			time_line_changes.push_back(time_line[i] - time_line[i-1]);
		}
		changes.push_back(time_line_changes);
	}

	return changes;
}

class Threshold
{
	public:
		Threshold(double decay, double reset_rate)
			: _f(0.0), _decay(decay), _reset_rate(reset_rate)
		{}

		void dec() { _f *= _decay; }
		void reset(double value)
		{
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

std::vector<unsigned int> get_event_positions(const std::vector<float>& time_line)
{
	std::vector<unsigned int> positions;
	Threshold threshold(0.85, 1.5);
	unsigned int position = 0;
	for (float f : time_line)
	{
		if (threshold.undercut(f))
		{
			positions.push_back(position);
		}
		threshold.reset(f);
		position++;
		threshold.dec();
	}

	return positions;
}

EventList BeatEventGenerator::compute(const essentia::Pool& pool) const
{
	EventList event_list;
	std::vector<std::vector<essentia::Real>> bark_bands = pool.value<std::vector<std::vector<essentia::Real>>>(data_identifier::BARK_BANDS);

	std::vector<std::vector<float>> changes = calculate_changes(bark_bands);

	std::vector<unsigned int> positions;

	for (const std::vector<float>& time_line : changes)
	{
		std::vector<unsigned int> new_positions = get_event_positions(time_line);
		for (unsigned int pos : new_positions)
		{
			if (!misc::contains(positions, pos))
			{
				positions.push_back(pos);
			}
		}
	}

	std::cout << "found: " << positions.size() << std::endl;

	for (unsigned int pos : positions)
	{
		Event e(BeatEvent(1.f), pos*(1024.f / 44100.f));
		event_list.push_back(e);
	}

	return event_list;
}
