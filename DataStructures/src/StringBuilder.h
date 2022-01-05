#pragma once
#include "MyString.h"
#include <memory>

namespace ds {

	class StringBuilder {
	public:
		void Append(const ds::String&);
		void Append(const char*);
		void Append(const char);

		void operator+=(const ds::String&);
		void operator+=(const char*);
		void operator+=(const char);

		bool IsEmpty() const;

		ds::String ToString() const;
	private:
		size_t capacity = 0;
		size_t size = 0;
		std::unique_ptr<char[]> array;

		void AppendCharArray(const char*, size_t);
		void GrowCapacity(const size_t);
	};

}
