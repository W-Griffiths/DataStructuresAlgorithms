#pragma once
#include <memory>
#include "Array.h"

namespace ds {
	class String final {
	public:
		String(const char*);
		String(const Array<char>&);

		size_t Length() const;
		bool IsEmpty() const;

		char& operator[](const size_t);
		char operator[](const size_t) const;

		//--- String comparisons
		bool operator==(const String&) const;
		bool operator!=(const String&) const;
		bool operator<(const String&) const;
		bool operator>(const String&) const;
		bool operator<=(const String&) const;
		bool operator>=(const String&) const;

		//--- C-String Comparisons
		bool operator==(const char*) const;
		bool operator!=(const char*) const;

	private:
		const size_t length;
		const std::unique_ptr<char[]> array;
	};
}
