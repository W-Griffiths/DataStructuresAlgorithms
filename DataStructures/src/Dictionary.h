#pragma once
#include "HashTable.h"
#include <stdexcept>

namespace ds {
	template <typename Key, typename Value>
	struct KeyValuePair {
		KeyValuePair(const Key& k, const Value& v) : key(k), value(v) {}
		const Key key;
		Value value;
	};

	template <typename Key, typename Value>
	class Dictionary : public HashTable<KeyValuePair<Key, Value>, Key> {
	public:

		using KV = KeyValuePair<Key, Value>;
		Dictionary() : HashTable< KV, Key >( [] (const KV& pair) -> const Key& { return pair.key; } ) {}

		Dictionary(const Dictionary& other) = delete;
		Dictionary& operator=(const Dictionary& other) = delete;

		Value& operator[] (const Key& key) {
			auto [found, value] = HashTable<KV, Key>::Search(key);

			if (found) {
				return value->value;
			}
			else {
				const KV newKV{ key, Value{} };
				HashTable<KV, Key>::Add(newKV);
				auto [_, value] = HashTable<KV, Key>::Search(key);
				return value->value;
			}
		}

		const Value& operator[] (const Key& key) const {
			auto [found, value] = HashTable<KV, Key>::Search(key);

			if (found) {
				return value->value;
			}
			else {
				throw std::invalid_argument("Key not found");
			}
		}

	};
}
