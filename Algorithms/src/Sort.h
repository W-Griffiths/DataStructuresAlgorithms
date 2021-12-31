#pragma once
#include "Array.h"
#include "Utilities.h"
#include "Random.h"
#include "Iterators/RandomAccessIterator.h"
#include <stdexcept>

namespace alg {

	template<typename T>
	using RAI = RandomAccessIterator<T>;

	//----- Declarations
	template<typename T>
	void Quicksort(RAI<T> begin, RAI<T> end);

	template<typename T>
	void Quicksort(const ds::Array<T>& array);

	namespace {

		template<typename T>
		void quicksort(RAI<T> left, RAI<T> right);

		template<typename T>
		RAI<T> Partition(RAI<T> left, RAI<T> right);

	}

	template<typename T>
	void Shuffle(RAI<T> begin, RAI<T> end);

	template<typename T>
	void Shuffle(ds::Array<T>& array);
	//-----
	
	template<typename T>
	void Quicksort(RAI<T> begin, RAI<T> end) {
		Shuffle(begin, end);

		quicksort(begin, end);
	}

	template<typename T>
	void Quicksort(const ds::Array<T>& array) {
		Quicksort(array.begin(), array.end());
	}

	namespace {

		template<typename T>
		void quicksort(RAI<T> left, RAI<T> right) {
			if (left >= right) return;

			RAI<T> pivot = Partition(left, right);
			quicksort(left, pivot);
			quicksort(pivot+1, right);
		}

		template<typename T>
		RAI<T> Partition(RAI<T> left, RAI<T> right) {
			RAI<T> pivot = left;

			while (left < right) {
				while (*(++left) < *pivot) {
					if (left == right) break;
				}
				while (*(--right) > *pivot) {
					if (right == left) break;
				}
				if (left >= right) break;
				util::Swap(*left, *right);
			}
			--left;
			util::Swap(*pivot, *left);
			return left;
		}

	}

	template<typename T>
	void Shuffle(RAI<T> begin, RAI<T> end) {
		ptrdiff_t length = end - begin;
		if (length == 1) return;
		if (length < 1) {
			throw std::invalid_argument("Shuffle sequence length is negative.");
		}

		util::Random random(0, length - 1);

		for (ptrdiff_t i = 0; i < length; i++) {
			ptrdiff_t ri = random.Next();
			Swap(begin[i], begin[ri]);
		}
	}

	template<typename T>
	void Shuffle(ds::Array<T>& array) {
		Shuffle(array.begin(), array.end());
	}

}
