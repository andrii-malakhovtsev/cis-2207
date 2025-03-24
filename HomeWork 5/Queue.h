// Andrii Malakhovtsev
// CIS 2207 501
// 03.09.2025
// Palindrome-recognition algorithm

#ifndef QUEUE_H
#define QUEUE_H

#include "QueueInterface.h"
#include <stdexcept>

template <typename ItemType>
class Queue : public QueueInterface<ItemType> {
private:
	struct Node {
		ItemType item;
		Node* next;
	};
	Node* frontPtr;
	Node* backPtr;

public:
	Queue() : frontPtr(nullptr), backPtr(nullptr) {}

	bool isEmpty() const override {
		return frontPtr == nullptr;
	}

	bool enqueue(const ItemType& newEntry) override {
		Node* newNode = new Node{ newEntry, nullptr };
		if (isEmpty()) {
			frontPtr = newNode;
		}
		else {
			backPtr->next = newNode;
		}
		backPtr = newNode;
		return true;
	}

	bool dequeue() override {
		if (isEmpty()) return false;
		Node* nodeToDelete = frontPtr;
		frontPtr = frontPtr->next;
		if (frontPtr == nullptr) {
			backPtr = nullptr;
		}
		delete nodeToDelete;
		return true;
	}

	ItemType peekFront() const override {
		if (isEmpty()) throw std::runtime_error("Queue is empty");
		return frontPtr->item;
	}

	~Queue() {
		while (!isEmpty()) {
			dequeue();
		}
	}
};

#endif
