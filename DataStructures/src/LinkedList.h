#pragma once
#include <utility>

namespace ds {
	template<typename T>
	class LinkedList {
	public:
		LinkedList() {}
		LinkedList(LinkedList&) = delete;
		LinkedList& operator=(LinkedList&) = delete;

		~LinkedList() {
			Node* link = first;
			while (link) {
				Node* next = link->next;
				delete link;
				link = next;
			}
		}

		void Insert(const T& value) {
			Node* newNode = new Node(value);
			newNode->next = first;
			first = newNode;
		}
		void Insert(T&& value) {
			Node*const newNode = new Node(std::move(value));
			newNode->next = first;
			first = newNode;
		}

	private:

		struct Node {
			Node(const T& val) : value(val) {}
			Node(T&& val) : value(std::move(val)) {}

			T value;
			Node* next = nullptr;
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

			bool operator==(const Iterator& other) const {
				return current == other.current;
			}
			bool operator!=(const Iterator& other) const {
				return !operator==(other);
			}

			bool PointsToEnd() const { return current == nullptr; }

		private:
			Node* current;
		};

		Iterator begin() const {
			return Iterator(first);
		}
		Iterator end() const {
			return Iterator(nullptr);
		}
	};
}
