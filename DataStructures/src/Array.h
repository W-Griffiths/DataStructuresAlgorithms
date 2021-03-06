#pragma once
#include "Iterators/RandomAccessIterator.h"
#include <memory>
#include <string>

namespace ds {
	template<typename T>
	class Array {
	public:

		Array(size_t size) : array(std::make_unique<T[]>(size)), size(size) {}

		Array(const char* string, const size_t size) : array(std::make_unique<T[]>(size)), size(size) {
			for (size_t i = 0; i < size; i++) {
				array[i] = string[i];
			}
		}

		Array(const std::string string) : array(std::make_unique<T[]>(string.length())), size(string.length()) {
			for (size_t i = 0; i < string.length(); i++) {
				array[i] = string[i];
			}
		}

		static Array<T> Empty() {
			return Array<T>(0);
		}

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

		void SetAll(T value) {
			for (size_t i = 0; i < size; i++)
			{
				array[i] = value;
			}
		}

		constexpr size_t Size() const {
			return size;
		}

		constexpr bool IsEmpty() const {
			return Size() == 0;
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
