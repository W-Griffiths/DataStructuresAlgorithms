#pragma once
#include "Iterators/RandomAccessIterator.h"
#include <memory>

namespace ds {
	template<typename T>
	class Array {
	public:

		Array(size_t size) : array(std::make_unique<T[]>(size)), size(size) {}

		Array(const Array& other) : array(std::make_unique<T[]>(other.size)), size(other.size) {
			for (size_t i = 0; i < size; i++)
			{
				array[i] = other[i];
			}
		}
		Array& operator=(const Array& other) = delete;

		T& operator[] (size_t index) {
			return array[index];
		}
		const T& operator[](size_t index) const {
			return array[index];
		}

		constexpr size_t Size() const {
			return size;
		}

		bool operator==(const Array& other) const {
			if (Size() != other.Size()) {
				return false;
			}

			for (size_t i = 0; i < Size(); i++) {
				if (array[i] != other.array[i]) {
					return false;
				}
			}

			return true;
		}
		bool operator!=(const Array& other) const { return !operator==(other); }

	private:

		std::unique_ptr<T[]> array;
		const size_t size;

	public:

		using Iterator = RandomAccessIterator<T>;

		Iterator begin() const {
			return Iterator(array.get());
		}
		Iterator end() const {
			return Iterator(array.get() + size);
		}
	};
}
