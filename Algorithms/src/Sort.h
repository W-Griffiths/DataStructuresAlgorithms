#pragma once
#include "Array.h"
#include "Utilities.h"
#include "Iterators/RandomAccessIterator.h"

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
	//-----
	
	template<typename T>
	void Quicksort(RAI<T> begin, RAI<T> end) {
		util::Shuffle(begin, end);

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

}
