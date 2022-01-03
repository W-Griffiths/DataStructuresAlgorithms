#pragma once
#include <memory>
#include "Array.h"
#include "Iterators/RandomAccessIterator.h"

namespace ds {
	class String final {
	public:
		String(const char*);
		String(const Array<char>&);

		String(const String& other);

		size_t Length() const;
		bool IsEmpty() const;

		char& operator[](const size_t);
		char operator[](const size_t) const;

		String Append(const String&) const;
		String Append(const char*) const;

		/// <summary>
		/// Converts any English alphabet characters to upper case.
		/// Modifies the string in-place.
		/// </summary>
		void ToUpper();
		String ToUpper() const;

		/// <summary>
		/// Converts any English alphabet characters to lower case.
		/// Modifies the string in-place.
		/// </summary>
		void ToLower();
		String ToLower() const;

		bool IsAlphabetic() const;
		bool IsAlphaNumeric() const;

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
		bool operator<(const char*) const;
		bool operator>(const char*) const;
		bool operator<=(const char*) const;
		bool operator>=(const char*) const;

	private:
		const size_t length;
		const std::unique_ptr<char[]> array;

		String(const size_t);

	public:
		static String Empty();

	public:
		using Iterator = RandomAccessIterator<char>;

		Iterator begin() const {
			return Iterator(array.get());
		}
		Iterator end() const {
			return Iterator(array.get() + length);
		}
	};
}
