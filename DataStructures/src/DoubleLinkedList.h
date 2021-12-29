#pragma once
#include <stdexcept>

namespace ds {
	
	template<typename T>
	class DoubleLinkedList {
	public:
		DoubleLinkedList() {
			endNode = Node::EndNode();
			last = endNode;
			first = endNode;
		}

		DoubleLinkedList(DoubleLinkedList&) = delete;
		DoubleLinkedList& operator=(DoubleLinkedList&) = delete;

		~DoubleLinkedList() {
			Node* link = first;
			while (link) {
				Node* next = link->next;
				delete link;
				link = next;
			}
		}

		void PushBack(const T& value) {
			Node* newNode = new Node(value);

			if (IsEmpty()) {
				InsertFirstNode(newNode);
				return;
			}

			last->next = newNode;
			newNode->prev = last;
			newNode->next = endNode;
			endNode->prev = newNode;
			last = newNode;
		}

		void PushFront(const T& value) {
			Node* newNode = new Node(value);

			if (IsEmpty()) {
				InsertFirstNode(newNode);
				return;
			}

			newNode->next = first;
			first->prev = newNode;
			first = newNode;
		}

		T PopBack() {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Pop - list is empty");
			}
			#endif

			Node* pop = last;
			endNode->prev = pop->prev;
			if (pop->prev) {
				pop->prev->next = endNode;
				last = pop->prev;
			}
			else {
				// Back to empty list
				last = endNode;
				first = endNode;
			}

			T popValue = pop->value;
			delete pop;
			return popValue;
			
		}

		T PopFront() {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Pop - list is empty");
			}
			#endif

			Node* pop = first;
			first = pop->next;
			first->prev = nullptr;

			T popValue = pop->value;
			delete pop;
			return popValue;
		}

		T& PeekBack() const {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Peek - list is empty");
			}
			#endif

			return last->value;

		}

		T& PeekFront() const {
			#ifdef _DEBUG
			if (IsEmpty()) {
				throw std::out_of_range("Cannot Peek - list is empty");
			}
			#endif

			return first->value;
		}

		bool IsEmpty() const {
			return first == endNode;
		}

	private:

		struct Node {
			Node(const T& val) : value(val) {}
			Node(T&& val) : value(std::move(val)) {}

			static Node* EndNode() {
				return new Node();
			}

			T value;
			Node* next = nullptr;
			Node* prev = nullptr;

		private:
			Node() {}
		};

		Node* first = nullptr;
		Node* last = nullptr;
		Node* endNode = Node::EndNode();

		void InsertFirstNode(Node* const newNode) {
			newNode->next = endNode;
			endNode->prev = newNode;
			last = newNode;
			first = last;
		}

	public:

		class Iterator {
		public:
			Iterator(Node* node) : current(node) { }

			T& operator*() {
				return current->value;
			}

			Iterator& operator++() {
				current = current->next;
				return *this;
			}
			Iterator operator++(int) {
				Iterator iter(current);
				++(*this);
				return iter;
			}
			Iterator& operator--() {
				#ifdef _DEBUG
				if (current->prev == nullptr) {
					throw std::out_of_range("Cannot decrement iterator past beginning");
				}
				#endif

				current = current->prev;
				return *this;
			}
			Iterator operator--(int) {
				Iterator iter(current);
				--(*this);
				return iter;
			}

			bool operator==(const Iterator& other) const {
				return current == other.current;
			}
			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}

		private:
			Node* current;
		};

		Iterator begin() const {
			return Iterator(first);
		}
		Iterator end() const {
			return Iterator(endNode);
		}
	};

}
