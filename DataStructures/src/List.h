#pragma once

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

		class Iterator {
		public:
			Iterator(T* address) : positionPtr(address) { }

			T& operator*() {
				return *positionPtr;
			}

			Iterator& operator++() {
				positionPtr++;
				return *this;
			}
			Iterator operator++(int) {
				Iterator iter(positionPtr);
				++(*this);
				return iter;
			}
			Iterator& operator--() {
				positionPtr--;
				return *this;
			}
			Iterator operator--(int) {
				Iterator iter(positionPtr);
				--(*this);
				return iter;
			}

			Iterator operator+(int length) {
				return Iterator(positionPtr + length);
			}
			Iterator operator-(int length) {
				return Iterator(positionPtr - length);
			}

			bool operator==(const Iterator& other) const {
				return positionPtr == other.positionPtr;
			}
			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}
		private:
			T* positionPtr;
		};

		Iterator begin() {
			return Iterator(array);
		}
		Iterator end() {
			return Iterator(array + size);
		}
	};
}
