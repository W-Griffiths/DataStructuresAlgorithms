#include "StringUtilities.h"

size_t CStringLength(const char* cString) {
	size_t len = 0;
	while (cString[len] != '\0') {
		len++;
	}
	return len;
}
