#pragma once
#include <memory>
#include <stdexcept>

namespace ds {

	template<typename T>
	class Stack {
	public:
		T Peek() const {
			if (IsEmpty()) {
				throw std::out_of_range("Invalid Peek - No elements in collection");
			}

			return items[size - 1];
		}

		T& Pop() {
			if (IsEmpty()) {
				throw std::out_of_range("Invalid Pop - No elements in collection");
			}

			if (BelowMinCapacity()) {
				DecreaseCapacity();
			}

			return items[--size];
		}

		void Push(const T item) {
			if (size == capacity) {
				IncreaseCapacity();
			}

			items[size++] = item;
		}

		size_t Size() const {
			return size;
		}

		bool IsEmpty() const {
			return Size() == 0;
		}

	private:
		std::unique_ptr<T[]> items = std::make_unique<T[]>(1);
		size_t size = 0;
		size_t capacity = 1;
		const float MinLoadFactor = 0.25f;

		void IncreaseCapacity() {
			capacity *= 2;
			MoveItems();
		}

		void DecreaseCapacity() {
			capacity /= 2;
			MoveItems();
		}

		void MoveItems() {
			auto newItems = std::make_unique<T[]>(capacity);
			for (size_t i = 0; i < size; i++)
			{
				newItems[i] = items[i];
			}
			items = std::move(newItems);
		}

		bool BelowMinCapacity() const {
			return ( static_cast<float>(size) / static_cast<float>(capacity) ) < MinLoadFactor;
		}
	};

}
