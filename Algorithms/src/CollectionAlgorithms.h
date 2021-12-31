#pragma once
#include <stdexcept>
#include "Iterators/RandomAccessIterator.h"

namespace alg {

	template<typename T>
	using RAI = RandomAccessIterator<T>;

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
		}
		else {
			// Shift left
			for (ptrdiff_t i = 0; i < length; i++) {
				begin[i + amount] = begin[i];
			}
		}
	}

}
