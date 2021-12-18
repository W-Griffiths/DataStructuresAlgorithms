#pragma once
#include "Iterators/RandomAccessIterator.h"

namespace ds {
	template<typename T, size_t size>
	class StackArray {
	public:

		T& operator[] (size_t index) {
			return array[index];
		}
		const T& operator[](size_t index) const {
			return array[index];
		}

		constexpr size_t Size() const {
			return size;
		}

	private:

		T array[size];

	public:

		using Iterator = RandomAccessIterator<T>;

		Iterator begin() {
			return Iterator(array);
		}
		Iterator end() {
			return Iterator(array + size);
		}
	};
}
