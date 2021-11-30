#pragma once
#include "LinkedList.h"
#include <functional>
#include <memory>

namespace ds {
	template <typename T>
	class HashTable {
	public:

		HashTable() : arraySize(7), array(new LinkedList<T>[arraySize]), numEntries(0) {}

		virtual ~HashTable() {
			delete[] array;
		}

		void Add(const T& value) {
			size_t index = GetIndex(value);
			array[index].Insert(value);

			numEntries++;
			CheckForTableResize();
		}

		bool Contains(const T& value) const {
			auto& [result, _] = Search(value);
			return result;
		}

	private:
		size_t arraySize;
		LinkedList<T>* array;

		size_t numEntries;
		const float maxLoadFactor = 0.8f;

		const std::hash<T> hasher;

		const std::pair<bool, const T*> Search(const T& value) const {
			size_t index = GetIndex(value);
			auto& listToSearch = array[index];
			for (const T& item : listToSearch) {
				if (item == value) {
					return { true, &value };
				}
			}
			return { false, nullptr };
		}

		const size_t Hash(const T& value) const {
			return hasher(value);
		}

		const size_t GetIndex(const T& value) const {
			return Hash(value) % arraySize;
		}

		void CheckForTableResize();
		void IncreaseTableSize();
		void Rehash(const size_t oldSize);

	public:

		class Iterator {
		public:

			static Iterator BeginIterator(LinkedList<T>* beginArrayPtr, size_t length) {
				Iterator iterator{ beginArrayPtr, beginArrayPtr->begin() };
				iterator.end = std::make_shared<Iterator>(EndIterator(beginArrayPtr + length));

				// Make sure the iterator points to the first valid element
				if (!iterator.PointsToEnd() && iterator.iter.PointsToEnd()) {
					++iterator;
				}

				return iterator;
			}

			static const Iterator EndIterator(LinkedList<T>* endArrayPtr) {
				auto* lastArrayPtr = endArrayPtr - 1;
				return Iterator{ lastArrayPtr, lastArrayPtr->end() };
			}

			const T& operator*() {
				return *iter;
			}

			Iterator& operator++() {
				if (!iter.PointsToEnd()) {
					iter++;
					return *this;
				}

				while (!PointsToEnd() && iter.PointsToEnd()) {
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
			Iterator(LinkedList<T>* arrayPtr, typename LinkedList<T>::Iterator iter) : arrayPtr(arrayPtr), iter(iter) { }

			LinkedList<T>* arrayPtr;
			typename LinkedList<T>::Iterator iter;
			std::shared_ptr<Iterator> end;

			bool PointsToEnd() {
				return *this == *end;
			}
		};

		Iterator begin() const {
			return Iterator::BeginIterator(array, arraySize);
		}
		const Iterator end() const {
			return Iterator::EndIterator(array + arraySize);
		}

	};

	template<typename T>
	void HashTable<T>::CheckForTableResize() {
		const float loadFactor = static_cast<float>(numEntries) / static_cast<float>(arraySize);
		if (loadFactor > maxLoadFactor) {
			IncreaseTableSize();
		}
		
	}
	template<typename T>
	void HashTable<T>::IncreaseTableSize() {
		const size_t oldSize = arraySize;
		// TODO - lookup next prime after doubling?
		arraySize = (arraySize * 2) + 1; // Guarantees odd number

		Rehash(oldSize);
	}
	template<typename T>
	void HashTable<T>::Rehash(const size_t oldSize) {
		LinkedList<T>* oldArray = array;
		array = new LinkedList<T>[arraySize];

		for (size_t i = 0; i < oldSize; i++) {
			for (auto& entry : oldArray[i]) {
				Add(entry);
			}
		}

		delete[] oldArray;
	}

}
