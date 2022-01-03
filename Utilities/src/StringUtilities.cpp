#include "StringUtilities.h"

size_t CStringLength(const char* cString) {
	size_t len = 0;
	while (cString[len] != '\0') {
		len++;
	}
	return len;
}

bool IsAlphabetic(const char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ');
}

bool IsAlphaNumeric(const char c) {
	return IsAlphabetic(c) || (c >= '0' && c <= '9');
}
