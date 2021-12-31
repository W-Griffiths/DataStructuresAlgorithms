#include "MyString.h"
#include "MyMath.h"
#include "StringUtilities.h"
#include <stdexcept>

namespace ds {
	String::String(const char* cString) : length(CStringLength(cString)), array(std::make_unique<char[]>(length)) {
		for (size_t i = 0; i < length; i++) {
			array[i] = cString[i];
		}
	}

	String::String(const Array<char>& array) : length(array.Size()), array(std::make_unique<char[]>(length)) {
		for (size_t i = 0; i < length; i++) {
			this->array[i] = array[i];
		}
	}

	size_t String::Length() const {
		return length;
	}

	bool String::IsEmpty() const {
		return length == 0;
	}

	char& String::operator[](const size_t index) {
		#ifdef _DEBUG
		if (index >= length) {
			throw std::out_of_range("Index is larger than the string length.");
		}
		#endif

		return array[index];
	}

	char String::operator[](const size_t index) const {
		#ifdef _DEBUG
		if (index >= length) {
			throw std::out_of_range("Index is larger than the string length.");
		}
		#endif

		return array[index];
	}

	bool String::operator==(const String& other) const {
		if (length != other.length) {
			return false;
		}
		
		for (size_t i = 0; i < length; i++) {
			if (array[i] != other.array[i]) {
				return false;
			}
		}
		
		return true;
	}

	bool String::operator!=(const String& other) const {
		return !operator==(other);
	}

	bool String::operator<(const String& other) const {
		// Use shortest length so we don't overflow
		size_t len = Min(length, other.length);
		for (size_t i = 0; i < len; i++) {
			if (array[i] == other.array[i]) {
				continue;
			}
			else {
				if (array[i] < other.array[i]) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// Strings are equal at this point
		if (length < other.length) {
			return true;
		}
		else {
			return false;
		}
	}

	bool String::operator>(const String& other) const {
		// Use shortest length so we don't overflow
		size_t len = Min(length, other.length);
		for (size_t i = 0; i < len; i++) {
			if (array[i] == other.array[i]) {
				continue;
			}
			else {
				if (array[i] > other.array[i]) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// Strings are equal at this point
		if (length > other.length) {
			return true;
		}
		else {
			return false;
		}
	}

	bool String::operator<=(const String& other) const {
		return !operator>(other);
	}

	bool String::operator>=(const String& other) const {
		return !operator<(other);
	}
	
	bool String::operator==(const char* cString) const {
		for (size_t i = 0; i < length; i++) {
			if (array[i] != cString[i]) {
				return false;
			}
		}
		if (cString[length] == '\0') {
			return true;
		}
		else {
			return false;
		}
	}

	bool String::operator!=(const char* cString) const {
		return !operator==(cString);
	}

	bool String::operator<(const char* cString) const {
		size_t otherLength = CStringLength(cString);
		size_t len = Min(length, otherLength);
		for (size_t i = 0; i < len; i++) {
			if (array[i] == cString[i]) {
				continue;
			}
			else {
				if (array[i] < cString[i]) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// Strings are equal at this point
		if (length < otherLength) {
			return true;
		}
		else {
			return false;
		}
	}

	bool String::operator>(const char* cString) const {
		size_t otherLength = CStringLength(cString);
		size_t len = Min(length, otherLength);
		for (size_t i = 0; i < len; i++) {
			if (array[i] == cString[i]) {
				continue;
			}
			else {
				if (array[i] > cString[i]) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		// Strings are equal at this point
		if (length > otherLength) {
			return true;
		}
		else {
			return false;
		}
	}

	bool String::operator<=(const char* cString) const {
		return !operator>(cString);
	}

	bool String::operator>=(const char* cString) const {
		return !operator<(cString);
	}

}
