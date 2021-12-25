#pragma once
#include "Iterators/RandomAccessIterator.h"

namespace ds {

	template<typename T>
	class List {
	public:
		List() : List(1) {}

		List(size_t reserved)
			: capacity(reserved) {
			if (reserved < 1) {
				capacity = 1;
			}

			array = AllocateArray(capacity);
		}

		~List() {
			delete[] array;
		}

		size_t Size() const { return size; }

		bool IsEmpty() const { return Size() == 0; }

		void Add(T& obj) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			array[size++] = obj;
		}

		void Add(T&& obj) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			array[size++] = std::move(obj);
		}

		T& operator[](size_t index) {
			return array[index];
		}

		const T& operator[](size_t index) const {
			return array[index];
		}

	private:
		T* array;
		size_t capacity;
		size_t size = 0;

		void IncreaseCapacity() {
			capacity *= 2;

			T* newArray = AllocateArray(capacity);
			for (size_t i = 0; i < size; i++)
			{
				newArray[i] = std::move(array[i]);
			}
			delete[] array;
			array = newArray;
		}

		inline T* AllocateArray(size_t length) {
			return new T[length];
		}

	public:

		using Iterator = RandomAccessIterator<T>;

		Iterator begin() const {
			return Iterator(array);
		}
		Iterator end() const {
			return Iterator(array + size);
		}
	};
}
