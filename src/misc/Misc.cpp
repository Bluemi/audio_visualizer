#include "Misc.hpp"

#include <random>

namespace misc {
	Matrix transpose(const Matrix& input) {
		Matrix transposed(input[0].size());

		for (std::vector<float>& v : transposed) {
			v = std::vector<float>(input.size());
		}

		for (unsigned int band_index = 0; band_index < input.size(); band_index++) {
			for (unsigned int f_index = 0; f_index < input[band_index].size(); f_index++) {
				transposed[f_index][band_index] = input[band_index][f_index];
			}
		}

		return transposed;
	}

	Matrix calculate_changes(const Matrix& input) {
		Matrix changes;

		for (const std::vector<float>& time_line : input) {
			std::vector<float> time_line_changes { 0.f };
			for (unsigned int i = 1; i < time_line.size(); i++) {
				time_line_changes.push_back(time_line[i] - time_line[i-1]);
			}
			changes.push_back(time_line_changes);
		}

		return changes;
	}

	std::default_random_engine _generator;

	std::string vec_to_string(const glm::vec3& vec) {
		return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
	}

	float generate_float(float mean, float stddev) {
		if (stddev == 0.f) {
			return mean;
		}
		std::normal_distribution<float> distribution(mean, stddev);
		return distribution(_generator);
	}

	int generate_int(int mean, int stddev) {
		return (std::rand() % (stddev*2+1)) - stddev + mean;
	}

	unsigned int generate_uint(unsigned int min, unsigned int max) {
		assert(min <= max);
		const unsigned int width = max - min;
		const unsigned int n = std::rand() % (width+1);
		return n + min;
	}
}

namespace math {
	bool is_included(const glm::vec3& position, const glm::vec3& center, const glm::vec3& size) {
		bool included = true;
		for (auto dimension = 0; dimension < position.length(); dimension++) {
			if (position[dimension] < (center[dimension] - size[dimension])) {
				included = false;
				break;
			}
			if (position[dimension] > (center[dimension] + size[dimension])) {
				included = false;
				break;
			}
		}
		return included;
	}
}
