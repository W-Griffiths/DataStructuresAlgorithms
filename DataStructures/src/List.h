#pragma once
#include <new>

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
			DeleteArray();
		}

		const size_t Size() const { return size; }

		void Add(T& obj) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			new (&array[size++]) T(obj);
		}

		void Add(T&& obj) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			new (&array[size++]) T(std::move(obj));
		}

		T& operator[](size_t index) {
			return array[index];
		}

		const T& operator[](size_t index) const {
			return array[index];
		}

		template<typename... Args>
		void Emplace(Args&&... args) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			new (&array[size++]) T(std::forward<Args>(args)...);
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
				//newArray[i] = std::move(array[i]);
				new (&newArray[i]) T(std::move(array[i]));
			}
			DeleteArray();
			array = newArray;
		}

		T* AllocateArray(size_t length) {
			return static_cast<T*>(::operator new[] (length * sizeof(T)));
		}

		void DeleteArray() {
			// Call destructors in reverse
			size_t i = size;
			while (true)
			{
				if (i == 0) break;
				i--;
				array[i].~T();
			}
			::operator delete[] (array);
		}

	};

}
