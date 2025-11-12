#pragma once
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
struct Node {
    T data;
    Node* prev;
    Node* next;
};
public:
	// Behaviors
	void printForward() const;
	void printReverse() const;

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
		return this->count;
	};
	Node* getHead() {
		return this->head;
	};
	const Node* getHead() const {
		return this->head;
	};
	Node* getTail() {
		return this->tail;
	};
	const Node* getTail() const {
		return this->tail;
	};

	// Insertion
	void addHead(const T& data) {
		Node* n = new Node{data, nullptr, head};
		head->prev = n;
		count++;
	};
	void addTail(const T& data) {
		Node* n = new Node{data, tail, nullptr};
		tail->next = n;
		count++;
	};

	void clearInternal() {
		Node* old = head;
		delete old;

		head = nullptr;
		tail = nullptr; 

		count = 0;
	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {
			return false;
		}
		if (this->count == 1) clearInternal();
		Node* oldptr = this->head;
		this->head = this->head.next;
		this->head->prev = nullptr;
		delete oldptr;
		count--;
		return true;
	};

	bool removeTail() {
		if (tail == nullptr) {
			return false;
		}
		if (count == 1) clearInternal();
		Node* oldptr = tail;
		tail = tail.prev;
		tail->next = nullptr;
		delete oldptr;
		count--;
		return true;
	};

	void clear() {
		while (removeHead()) {
			continue;
		}
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) { return *this; }

		this->Clear();

		count = other.count;
		head = other.head;
		tail = other.tail;

		other.count = 0;
		other.head = nullptr; 
		other.tail = nullptr;

		return *this;
	};
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) { return *this; }
		
		Clear();

		Node* node = rhs.head;
		while (node) {
			addTail(node->data);
			node = node->next;
		}

		return *this;
	};

	// Construction/Destruction
	LinkedList() {
		count = 0; 
		head = nullptr; 
		tail = nullptr;
	};
	LinkedList(const LinkedList<T>& list) {
		head = nullptr; 
		tail = nullptr;
		count = 0;
		Node* temp = list.head; 
		while (temp) {
			addTail(temp->data);
			temp = temp->next;
		}
		count = list.count;

	};
	LinkedList(LinkedList<T>&& other) noexcept {
		this->count = other.count;
		this->head = other.head;
		this->tail = other.tail;

		other.count = 0;
		other.head = nullptr;
		other.tail = nullptr;
	};
	~LinkedList() {
		clear();
	};

private:
	// Stores pointers to first and last nodes and count
	Node* head;
	Node* tail;
	unsigned int count;

};


