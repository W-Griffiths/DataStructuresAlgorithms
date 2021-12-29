#include "Utilities.h"

namespace util {

	size_t StringLength(const char* stringPtr) {
		size_t length = 0;
		while (*stringPtr != '\0') {
			++length;
			++stringPtr;
		}
		return length;
	}

}
