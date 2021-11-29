#pragma once
#include <functional>
#include "LinkedList.h"

namespace ds {
	template <typename Key, typename Value>
	class HashTable {
	public:

		HashTable() : arraySize(7), array(new LinkedList<KeyValuePair>[arraySize]) {}

		~HashTable() {
			delete[] array;
		}

		void Add(const Key& key, const Value& val) {

		}

		Value& operator[] (const Key& key) {
			auto [found, value] = Search(key);
			
			size_t index = GetIndex(key);
			auto listToSearch = array[index];
			for (auto& kv : listToSearch) {
				if (kv.key == key) {
					return kv.value;
				}
			}
			// Key not found
			listToSearch.Insert({ key, Value{} });

		}

		const Value& operator[] (const Key& key) const {
			size_t index = GetIndex(key);
			auto listToSearch = array[index];
			for (auto& kv : listToSearch) {
				if (kv.key == key) {
					return kv.value;
				}
			}
			// Key not found
			throw std::invalid_argument("Key not found");
		}


	private:

		std::pair<bool, Value&> Search(const Key& key) const {
			size_t index = GetIndex(key);
			auto listToSearch = array[index];
			for (auto& kv : listToSearch) {
				if (kv.key == key) {
					return { true, kv.value };
				}
			}
			return { false, nullptr };
		}
		
		Value& CreateDefault(const Key& key) {

		}

		struct KeyValuePair {
			KeyValuePair(Key k, Value v) : key(k), value(v) {}
			Key key;
			Value value;
		};

		size_t arraySize;
		LinkedList<KeyValuePair>* array;

		const std::hash<Key> hasher;

		const size_t Hash(const Key& key) const {
			return hasher(key);
		}

		const size_t GetIndex(const Key& key) const {
			return Hash(key) % arraySize;
		}
	};
}
