#include "Misc.hpp"

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
}
