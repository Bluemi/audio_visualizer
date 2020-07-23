#ifndef __MISC_CLASS__
#define __MISC_CLASS__

#include <vector>
#include <string>
#include <glm/vec3.hpp>

namespace misc {
	template<typename T>
	bool contains(const std::vector<T>& vec, T item) {
		for (const auto t : vec)
			if (item == t)
				return true;
		return false;
	}

	// if using this Matrix definition the inner
	// vectors should all have the same size.
	using Matrix = std::vector<std::vector<float>>;

	Matrix transpose(const Matrix& input);
	Matrix calculate_changes(const Matrix& input);

	std::string vec_to_string(const glm::vec3& vec);

	float generate_float(float mean, float stddev);
	int generate_int(int mean, int stddev);
	unsigned int generate_uint(unsigned int min, unsigned int max);
}

namespace math {
	bool is_included(const glm::vec3& position, const glm::vec3& center, const glm::vec3& size);

	template<typename Num>
	Num limit(Num input, Num bot, Num top) {
		return std::max(bot, std::min(input, top));
	}

}

#endif
