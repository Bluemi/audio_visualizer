#ifndef __MISC_CLASS__
#define __MISC_CLASS__

#include <vector>

namespace misc
{
	template<typename T>
	bool contains(const std::vector<T>& vec, T item)
	{
		for (const auto t : vec)
			if (item == t)
				return true;
		return false;
	}
}

#endif
