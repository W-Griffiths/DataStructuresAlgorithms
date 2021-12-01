#pragma once
#include <utility>

namespace ds {
	template<typename T>
	class LinkedList {
	public:
		~LinkedList() {
			Node* link = first;
			while (link) {
				Node* next = link->next;
				delete link;
				link = next;
			}
		}

		void Insert(T& value) {
			Node* newNode = new Node(value);
			newNode->next = first;
			first = newNode;
		}
		void Insert(T&& value) {
			Node* newNode = new Node(std::move(value));
			newNode->next = first;
			first = newNode;
		}

	private:

		struct Node {
			Node(T& val) : value(val) {}
			Node(T&& val) : value(std::move(val)) {}

			Node* next = nullptr;
			T value;
		};

		Node* first = nullptr;

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

			const bool operator==(const Iterator& other) const {
				return current == other.current;
			}
			const bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}
		private:
			Node* current;
		};

		Iterator begin() {
			return Iterator(first);
		}
		Iterator end() {
			return Iterator(nullptr);
		}
	};
}
