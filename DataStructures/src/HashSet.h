#pragma once
#include "HashTable.h"

namespace ds {
	template <typename T>
	class HashSet : public HashTable<T> {
	public:

		virtual void Add(const T& value) {
			TryAdd(value);
		}

		/// <summary>
		/// Returns a bool indicating whether add was successful.
		/// </summary>
		/// <returns>Returns false if item already exists in the set.</returns>
		bool TryAdd(const T& value) {
			if (HashTable<T>::Contains(value)) {
				return false;
			}
			else {
				HashTable<T>::Add(value);
				return true;
			}
		}

	};
}
