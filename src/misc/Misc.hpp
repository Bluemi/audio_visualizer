#ifndef __MISC_CLASS__
#define __MISC_CLASS__

#include <vector>

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
}

#endif
