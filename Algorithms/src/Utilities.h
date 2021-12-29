#pragma once
#include "Iterators/RandomAccessIterator.h"
#include "Random.h"
#include "Array.h"
#include <stdexcept>
#include <string>

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

	template<typename T>
	void ShiftElements(RAI<T> begin, RAI<T> end, const ptrdiff_t amount);

	size_t CStringLength(const char*);
	std::string ToString(const ds::Array<char>);
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

	/// <summary>
	/// Moves the input sequence by the desired amount.
	/// Warning: This overwrites elements at the destination.
	/// </summary>
	template<typename T>
	void ShiftElements(RAI<T> begin, RAI<T> end, const ptrdiff_t amount) {
		ptrdiff_t length = end - begin;

		if (length == 0 || amount == 0) return;

		#ifdef _DEBUG
		if (length < 0) {
			throw std::invalid_argument("Element sequence length is negative.");
		}
		#endif

		if (amount > 0) {
			// Shift right
			for (ptrdiff_t i = length - 1; i >= 0; i--) {
				begin[i + amount] = begin[i];
			}
		} else{
			// Shift left
			for (ptrdiff_t i = 0; i < length; i++) {
				begin[i + amount] = begin[i];
			}
		}
	}

}
