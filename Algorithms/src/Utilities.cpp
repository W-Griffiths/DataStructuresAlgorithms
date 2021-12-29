#include "Utilities.h"
#include <sstream>

namespace util {

	size_t StringLength(const char* stringPtr) {
		size_t length = 0;
		while (*stringPtr != '\0') {
			++length;
			++stringPtr;
		}
		return length;
	}

	std::string ToString(const ds::Array<char> input) {
		std::stringstream ss;
		for (size_t i = 0; i < input.Size(); i++)
		{
			ss << input[i];
		}
		return ss.str();
	}

}
