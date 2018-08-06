#include "PartsDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"
#include <visualizer/misc/Math.hpp>

PartsDataGenerator::PartsDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

struct Window
{
	Window(unsigned int b, unsigned int e, float v) : begin(b), end(e), value(v) {}
	unsigned int get_size() const
	{
		return end - begin;
	}

	unsigned int begin;
	unsigned int end;
	float value;
};

bool should_windows_merge(const Window& w1, const Window& w2, float refinement)
{
	float value_diff = std::abs(w1.value - w2.value);
	unsigned int min_group_size = std::min(w1.get_size(), w2.get_size());
	float v = std::sqrt(min_group_size) * std::pow(value_diff * 1000.f, 4.f);
	// std::cout << "v: " << v << std::endl;
	return v < refinement;
}

Window merge_windows(const Window& w1, const Window& w2)
{
	float w1_influence = w1.get_size() / (w1.get_size() + w2.get_size());
	float value = w1_influence * w1.value + (1.f - w1_influence) * w2.value;

	// std::cout << "w1.size: " << w1.get_size() << " w2.size: " << w2.get_size() << std::endl;
	// std::cout << "w1.value: " << w1.value << " w2.value: " << w2.value << " v: " << value << std::endl;
	return Window(w1.begin, w2.end, value);
}

std::vector<Window> group_windows(const std::vector<Window>& windows, float refinement)
{
	std::vector<Window> grouped_windows;
	Window current_window = windows[0];

	for (auto iter = windows.cbegin()+1; iter != windows.cend(); ++iter)
	{
		if (should_windows_merge(current_window, *iter, refinement))
		{
			current_window = merge_windows(current_window, *iter);
		} else {
			grouped_windows.push_back(current_window);
			current_window = *iter;
		}
	}

	grouped_windows.push_back(current_window);

	return grouped_windows;
}

void PartsDataGenerator::compute()
{
	std::vector<float> arousal_timeline = _pool->value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);

	unsigned int frame_counter = 0;
	std::vector<Window> windows;

	for (auto iter = arousal_timeline.cbegin(); iter != arousal_timeline.cend(); ++iter)
	{
		windows.push_back(Window(frame_counter, frame_counter+1, *iter));
		frame_counter++;
	}

	// const std::vector<float> refinements { 1.f , 2.f, /* 3.f, 4.f */};

	for (double refinement = 1.0; windows.size() > 10; refinement *= 2.0)
	{
		windows = group_windows(windows, refinement);
		std::cout << "num groups: " << windows.size() << std::endl;
	}

	std::vector<float> parts;
	for (const Window& w : windows)
	{
		for (unsigned int i = 0; i < w.get_size(); i++)
		{
			parts.push_back(w.value);
		}
	}

	_pool->set(data_identifier::AROUSAL_DIFFS, parts);
}
