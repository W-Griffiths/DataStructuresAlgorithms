#pragma once
#include "Array.h"
#include <random>

namespace alg {

	template<typename T>
	void Shuffle(ds::Array<T>& array) {
		const size_t arraySize = array.Size();

		static std::default_random_engine generator; // state is saved between calls
		std::uniform_int_distribution<int> distribution(0, arraySize-1);

		for (size_t i = 0; i < arraySize; i++) {
			size_t ri = distribution(generator);
			Swap(array[i], array[ri]);
		}
	}

	template<typename T>
	void Swap( T& A, T& B) {
		T& temp = A;
		A = B;
		B = temp;
	}

}
