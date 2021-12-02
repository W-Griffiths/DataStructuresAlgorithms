#pragma once
#include "LinkedList.h"
#include <functional>
#include <memory>

namespace ds {
	template <typename T, typename SearchKey=T>
	class HashTable {
	public:

		using listType = LinkedList<T>;

		HashTable(std::function<const SearchKey&(const T&)> GetKey = [](const T& t) -> const SearchKey& {return t;})
			: arraySize(7), array(new listType[arraySize]), numEntries(0), hasher(), GetSearchKey(GetKey) { }

		HashTable(const HashTable& other) = delete;
		HashTable& operator=(const HashTable& other) = delete;

		virtual ~HashTable() {
			delete[] array;
		}

		virtual void Add(const T& value) {
			const SearchKey& key = GetSearchKey(value);
			size_t index = GetIndex(key);
			array[index].Insert(value);

			numEntries++;
			CheckForTableResize();
		}

		bool Contains(const SearchKey& searchKey) const {
			auto& [result, _] = Search(searchKey);
			return result;
		}

	protected:

		const std::pair<bool, T*> Search(const SearchKey& lookup) const {
			size_t index = GetIndex(lookup);
			auto& listToSearch = array[index];
			for (T& item : listToSearch) {
				if (GetSearchKey(item) == lookup) {
					return { true, &item };
				}
			}
			return { false, nullptr };
		}
	
	private:
		size_t arraySize;
		listType* array;

		size_t numEntries;
		const float maxLoadFactor = 0.8f;

		const std::hash<SearchKey> hasher;
		std::function<const SearchKey& (const T&)> GetSearchKey;

		const size_t Hash(const SearchKey& value) const {
			return hasher(value);
		}

		const size_t GetIndex(const SearchKey& value) const {
			return Hash(value) % arraySize;
		}

		void CheckForTableResize();
		void IncreaseTableSize();
		void Rehash(const size_t oldSize);

	public:

		class Iterator {
		public:

			static Iterator BeginIterator(listType* beginArrayPtr, size_t length) {
				Iterator iterator{ beginArrayPtr, beginArrayPtr->begin() };
				iterator.end = std::make_shared<Iterator>(EndIterator(beginArrayPtr + length));

				iterator.PointToFirstElement();

				return iterator;
			}

			static const Iterator EndIterator(listType* endArrayPtr) {
				auto* lastArrayPtr = endArrayPtr - 1;
				return Iterator{ lastArrayPtr, lastArrayPtr->end() };
			}

			const T& operator*() {
				return *iter;
			}

			Iterator& operator++() {
				++iter;

				while (!PointsToEnd() && iterPointsToEnd()) {
					arrayPtr++;
					iter = arrayPtr->begin();
				}
				return *this;
			}
			Iterator operator++(int) {
				Iterator iter = *this;
				++(*this);
				return iter;
			}

			const bool operator==(const Iterator& other) const {
				return arrayPtr == other.arrayPtr
					&& iter == other.iter;
			}
			const bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}

		private:
			Iterator(listType* arrayPtr, typename listType::Iterator iter) : arrayPtr(arrayPtr), iter(iter) { }

			listType* arrayPtr;
			typename listType::Iterator iter;
			std::shared_ptr<Iterator> end;

			bool PointsToEnd() const {
				return *this == *end;
			}
			bool iterPointsToEnd() const {
				return iter == arrayPtr->end();
			}
			void PointToFirstElement() {
				while (!PointsToEnd() && iterPointsToEnd()) {
					arrayPtr++;
					iter = arrayPtr->begin();
				}
			}

		};

		Iterator begin() const {
			return Iterator::BeginIterator(array, arraySize);
		}
		Iterator end() const {
			return Iterator::EndIterator(array + arraySize);
		}

	};

	template<typename T, typename HashKey>
	void HashTable<T, HashKey>::CheckForTableResize() {
		const float loadFactor = static_cast<float>(numEntries) / static_cast<float>(arraySize);
		if (loadFactor > maxLoadFactor) {
			IncreaseTableSize();
		}
		
	}
	template<typename T, typename HashKey>
	void HashTable<T, HashKey>::IncreaseTableSize() {
		const size_t oldSize = arraySize;
		// TODO - lookup next prime after doubling?
		arraySize = (arraySize * 2) + 1; // Guarantees odd number

		Rehash(oldSize);
	}
	template<typename T, typename HashKey>
	void HashTable<T, HashKey>::Rehash(const size_t oldSize) {
		listType* oldArray = array;
		array = new listType[arraySize];

		for (size_t i = 0; i < oldSize; i++) {
			for (auto& entry : oldArray[i]) {
				Add(entry);
			}
		}

		delete[] oldArray;
	}

}
