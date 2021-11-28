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
	};
}
