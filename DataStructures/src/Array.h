#pragma once

namespace ds {
	template<typename T, size_t size>
	class Array {
	public:

		Array() : array(new T[size]) {}
		~Array() {
			delete[] array;
		}

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
		T* array;

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

			const bool operator==(const Iterator& other) const {
				return positionPtr == other.positionPtr;
			}
			const bool operator!=(const Iterator& other) const {
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
