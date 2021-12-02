#pragma once

namespace ds {
	template<typename T>
	class Array {
	public:

		Array(size_t size) : array(new T[size]), size(size) {}

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

		T* array;
		const size_t size;

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
