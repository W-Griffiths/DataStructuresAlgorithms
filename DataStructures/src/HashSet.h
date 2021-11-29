#pragma once
#include "LinkedList.h"
#include <functional>

namespace ds {
	template <typename T>
	class HashSet {
	public:

		HashSet() : arraySize(7), array(new LinkedList<T>[arraySize]) {}

		~HashSet() {
			delete[] array;
		}

		void Add(const T& value) {

		}

		bool TryAdd(const T& value) {
			return true;
		}

		bool Contains(const T& value) {
			return false;
		}

	private:

		/*std::pair<bool, Value&> Search(const Key& key) const {
			size_t index = GetIndex(key);
			auto listToSearch = array[index];
			for (auto& kv : listToSearch) {
				if (kv.key == key) {
					return { true, kv.value };
				}
			}
			return { false, nullptr };
		}*/

		size_t arraySize;
		LinkedList<T>* array;

		const std::hash<T> hasher;

		const size_t Hash(const T& value) const {
			return hasher(value);
		}

		const size_t GetIndex(const T& value) const {
			return Hash(value) % arraySize;
		}
	};
}
