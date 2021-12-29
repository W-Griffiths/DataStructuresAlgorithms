#include "Utilities.h"
#include <sstream>

namespace util {

	size_t CStringLength(const char* CString) {
		size_t i = 0;
		while (CString[i] != '\0') {
			++i;
		}
		return i;
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
