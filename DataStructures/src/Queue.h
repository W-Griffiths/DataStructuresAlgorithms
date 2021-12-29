#pragma once
#include "DoubleLinkedList.h"
#include <stdexcept>

namespace ds {

	template<typename T>
	class Queue {
	public:
		void Enqueue(const T& obj) {
			size++;
			linkedList.PushBack(obj);
		}

		T Dequeue() {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Dequeue - queue is empty");
			}
			#endif

			size--;
			return linkedList.PopFront();
		}

		T Peek() const {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Peek - queue is empty");
			}
			#endif

			return linkedList.PeekFront();
		}

		size_t Size() {
			return size;
		}

		bool IsEmpty() const {
			return size == 0;
		}
	private:
		DoubleLinkedList<T> linkedList;
		size_t size = 0;
	};

}
