#include "StringBuilder.h"
#include "StringUtilities.h"

namespace ds {

	void StringBuilder::Append(const ds::String& string) {
		AppendCharArray(string.array.get(), string.Length());
	}

	void StringBuilder::Append(const char* cString) {
		const size_t len = CStringLength(cString);
		AppendCharArray(cString, len);
	}

	void StringBuilder::Append(const char c) {
		AppendCharArray(&c, 1);
	}

	bool StringBuilder::IsEmpty() const {
		return size == 0;
	}

	String StringBuilder::ToString() const {
		String string(size);

		for (size_t i = 0; i < size; i++) {
			string[i] = array[i];
		}

		return string;
	}

	void StringBuilder::AppendCharArray(const char* charArray, size_t len) {
		const size_t newSize = size + len;
		
		if (newSize > capacity) {
			GrowCapacity(newSize);
		}
		size = newSize;
		
		size_t ai = size - len;
		for (size_t i = 0; i < len; i++) {
			array[ai++] = charArray[i];
		}
	}

	void StringBuilder::GrowCapacity(const size_t newSize) {
		if (capacity == 0 && newSize > 0) {
			capacity = 1;
		}
		while (newSize > capacity) {
			capacity *= 2;
		}
		auto newArray = std::make_unique<char[]>(capacity);
		for (size_t i = 0; i < size; i++) {
			newArray[i] = array[i];
		}

		array = std::move(newArray);
	}

}
