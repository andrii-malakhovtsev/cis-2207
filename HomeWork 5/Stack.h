// Andrii Malakhovtsev
// CIS 2207 501
// 03.09.2025
// Palindrome-recognition algorithm

#ifndef STACK_H
#define STACK_H

#include "StackInterface.h"
#include <stdexcept>

template <typename ItemType>
class Stack : public StackInterface<ItemType> {
private:
	struct Node {
		ItemType item;
		Node* next;
	};
	Node* topPtr;

public:
	Stack() : topPtr(nullptr) {}

	bool isEmpty() const override {
		return topPtr == nullptr;
	}

	bool push(const ItemType& newEntry) override {
		Node* newNode = new Node{ newEntry, topPtr };
		topPtr = newNode;
		return true;
	}

	bool pop() override {
		if (isEmpty()) return false;
		Node* nodeToDelete = topPtr;
		topPtr = topPtr->next;
		delete nodeToDelete;
		return true;
	}

	ItemType peek() const override {
		if (isEmpty()) throw std::runtime_error("Stack is empty");
		return topPtr->item;
	}

	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}
};

#endif
