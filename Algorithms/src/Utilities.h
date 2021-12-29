#pragma once
#include "Iterators/RandomAccessIterator.h"
#include "Random.h"
#include "Array.h"
#include <stdexcept>

namespace util {
	
	template<typename T>
	using RAI = RandomAccessIterator<T>;

	//----- Declarations
	template<typename T>
	void Shuffle(RAI<T> begin, RAI<T> end);

	template<typename T>
	void Shuffle(ds::Array<T>& array);

	template<typename T>
	void Swap(T& A, T& B);

	size_t StringLength(const char*);
	//-----
	
	template<typename T>
	void Shuffle(RAI<T> begin, RAI<T> end) {
		ptrdiff_t length = end - begin;
		if (length == 1) return;
		if (length < 1) {
			throw std::invalid_argument("Shuffle sequence length is negative.");
		}

		Random random(0, length - 1);

		for (ptrdiff_t i = 0; i < length; i++) {
			ptrdiff_t ri = random.Next();
			Swap(begin[i], begin[ri]);
		}
	}

	template<typename T>
	void Shuffle(ds::Array<T>& array) {
		Shuffle(array.begin(), array.end());
	}

	template<typename T>
	void Swap(T& A, T& B) {
		T temp = A;
		A = B;
		B = temp;
	}

}
