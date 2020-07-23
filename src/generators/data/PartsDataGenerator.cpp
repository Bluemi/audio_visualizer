#include "PartsDataGenerator.hpp"

#include "../../data/DataIdentifier.hpp"
#include "misc/Misc.hpp"

PartsDataGenerator::PartsDataGenerator(essentia::Pool* pool, essentia::standard::AlgorithmFactory* algorithm_factory)
	: _pool(pool), _algorithm_factory(algorithm_factory)
{}

struct Window {
	Window(unsigned int b, unsigned int e, float v) : begin(b), end(e), value(v) {}
	unsigned int get_size() const {
		return end - begin;
	}

	bool operator<(const Window& w) { return this->begin < w.begin; }
	bool operator>(const Window& w) { return this->begin > w.begin; }
	bool operator<=(const Window& w) { return this->begin <= w.begin; }
	bool operator>=(const Window& w) { return this->begin >= w.begin; }

	unsigned int begin;
	unsigned int end;
	float value;
};

float should_windows_merge(const Window& w1, const Window& w2) {
	const float value_diff = std::abs(w1.value - w2.value);
	unsigned int min_group_size = std::min(w1.get_size(), w2.get_size());

	if (value_diff < std::numeric_limits<float>::min())
		return std::numeric_limits<float>::max();

	if (min_group_size == 1)
		return std::numeric_limits<float>::max();

	const float v = std::log(static_cast<float>(min_group_size)) * std::pow(value_diff, 2.0);

	return 1.f / v;
}

Window merge_windows(const Window& w1, const Window& w2) {
	const float value = w1.get_size() > w2.get_size() ? w1.value : w2.value;
	return Window(w1.begin, w2.end, value);
}

std::vector<float> get_merge_forces(const std::vector<Window>& windows) {
	std::vector<float> merge_forces;
	for (auto iter = windows.cbegin()+1; iter != windows.cend(); ++iter) {
		merge_forces.push_back(should_windows_merge(*(iter-1), *iter));
	}

	return merge_forces;
}

/*
 * Taken from:
 * https://stackoverflow.com/questions/25921706/creating-a-vector-of-indices-of-a-sorted-vector
 */
std::vector<unsigned int> get_indices(const std::vector<float>& vec) {
	std::vector<unsigned int> y(vec.size());
	std::size_t n(0);
	std::generate(std::begin(y), std::end(y), [&]{ return n++; });

	std::sort(std::begin(y), 
				std::end(y),
				[&](int i1, int i2) { return vec[i1] < vec[i2]; } );

	return y;
}

bool neighbour_free(const std::vector<bool>& used_windows, unsigned int index) {
	bool is_valid = true;
	if (used_windows[index])
		is_valid = false;

	if (used_windows[index+1])
		is_valid = false;

	return is_valid;
}

std::vector<unsigned int> get_max_force_indices(const std::vector<float>& forces) {
	std::vector<unsigned int> indices = get_indices(forces);
	int max_index = 0;
	for (int i : indices)
		if (max_index < i)
			max_index = i;

	std::vector<bool> used_windows(max_index+1);

	std::vector<unsigned int> filtered_indices;

	unsigned int counter = 0;

	for (auto iter = indices.rbegin(); iter != indices.rend(); ++iter) {
		if (neighbour_free(used_windows, *iter)) {
			filtered_indices.push_back(*iter);
			counter++;
			if (counter > forces.size()/5)
				break;

			used_windows[*iter] = true;
			if (used_windows.size() != (*iter)+1)
				used_windows[(*iter)+1] = true;
		}

	}

	return filtered_indices;
}

std::vector<Window> group_windows(const std::vector<Window>& windows) {
	std::vector<float> merge_forces = get_merge_forces(windows);
	std::vector<unsigned int> max_force_indices = get_max_force_indices(merge_forces);

	std::vector<Window> grouped_windows;

	for (unsigned int index : max_force_indices) {
		Window new_window = merge_windows(windows[index], windows[index+1]);
		grouped_windows.push_back(new_window);
	}

	std::sort(max_force_indices.begin(), max_force_indices.end());
	auto index_iter = max_force_indices.cbegin();

	bool skip_index_iter = false;
	for (unsigned int i = 0; i < windows.size(); i++) {
		while (*index_iter < i) {
			++index_iter;
			if (index_iter == max_force_indices.cend())
				skip_index_iter = true;
		}
		if ((not skip_index_iter) && (*index_iter == i)) {
			i++;
		} else {
			grouped_windows.push_back(windows[i]);
		}
	}

	std::sort(grouped_windows.begin(), grouped_windows.end());

	return grouped_windows;
}

const unsigned int WINDOW_SIZE = 1;

void PartsDataGenerator::compute() {
	std::cout << "Calculating Parts... " << std::flush;
	std::vector<float> arousal_timeline = _pool->value<std::vector<float>>(data_identifier::AROUSAL_TIMELINE);

	std::vector<Window> windows;
	Window current_window(0, 1, 0.f);
	float sum = 0.f;
	for (unsigned int frame_counter = 0; frame_counter < arousal_timeline.size(); frame_counter++) {
		sum += arousal_timeline[frame_counter];

		if (frame_counter % WINDOW_SIZE == 0) {
			current_window.end = frame_counter;
			current_window.value = sum / WINDOW_SIZE;
			windows.push_back(current_window);
			current_window.begin = frame_counter;
			sum = 0.f;
		}
	}

	while (windows.size() > 25) {
		windows = group_windows(windows);
	}

	std::vector<float> parts;
	for (const Window& w : windows) {
		for (unsigned int i = 0; i < w.get_size(); i++) {
			parts.push_back(w.value);
		}
	}

	_pool->set(data_identifier::AROUSAL_DIFFS, parts);

	std::cout << "Done." << std::endl;
}
