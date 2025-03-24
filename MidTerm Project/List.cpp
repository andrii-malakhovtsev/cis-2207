// Andrii Malakhovtsev
// CIS 2207 501
// 03.23.2025
// MidTerm Project - Rainfall Statistics

#include "List.h"
#include "MonthData.h"

#include <iostream>

template<class ItemType>
List<ItemType>::List() : headPtr(nullptr), itemCount(0) {}

template<class ItemType>
List<ItemType>::List(const List<ItemType>& aList) {
    itemCount = aList.itemCount;
    if (aList.headPtr == nullptr) {
        headPtr = nullptr;
    }
    else {
        Node<ItemType>* origChainPtr = aList.headPtr;
        headPtr = new Node<ItemType>(origChainPtr->getItem());
        Node<ItemType>* newChainPtr = headPtr;
        origChainPtr = origChainPtr->getNext();

        while (origChainPtr != nullptr) {
            ItemType nextItem = origChainPtr->getItem();
            Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
            newChainPtr->setNext(newNodePtr);
            newChainPtr = newChainPtr->getNext();
            origChainPtr = origChainPtr->getNext();
        }
    }
}

template<class ItemType>
List<ItemType>::~List() {
    clear();
}

template<class ItemType>
bool List<ItemType>::isEmpty() const {
    return itemCount == 0;
}

template<class ItemType>
int List<ItemType>::getLength() const {
    return itemCount;
}

template<class ItemType>
bool List<ItemType>::insert(int newPosition, const ItemType& newEntry) {
    if (newPosition >= 1 && newPosition <= itemCount + 1) {
        Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
        if (newPosition == 1) {
            newNodePtr->setNext(headPtr);
            headPtr = newNodePtr;
        }
        else {
            Node<ItemType>* prevNodePtr = getNodeAt(newPosition - 1);
            newNodePtr->setNext(prevNodePtr->getNext());
            prevNodePtr->setNext(newNodePtr);
        }
        itemCount++;
        return true;
    }
    return false;
}

template<class ItemType>
bool List<ItemType>::remove(int position) {
    if (position >= 1 && position <= itemCount) {
        Node<ItemType>* curNodePtr = nullptr;
        if (position == 1) {
            curNodePtr = headPtr;
            headPtr = headPtr->getNext();
        }
        else {
            Node<ItemType>* prevNodePtr = getNodeAt(position - 1);
            curNodePtr = prevNodePtr->getNext();
            prevNodePtr->setNext(curNodePtr->getNext());
        }
        curNodePtr->setNext(nullptr);
        delete curNodePtr;
        curNodePtr = nullptr;
        itemCount--;
        return true;
    }
    return false;
}

template<class ItemType>
void List<ItemType>::clear() {
    while (!isEmpty())
        remove(1);
}

template<class ItemType>
ItemType List<ItemType>::getEntry(int position) const throw(PrecondViolatedExcept) {
    if (position >= 1 && position <= itemCount) {
        Node<ItemType>* nodePtr = getNodeAt(position);
        return nodePtr->getItem();
    }
    throw PrecondViolatedExcept("getEntry() called with an empty list or invalid position.");
}

template<class ItemType>
ItemType List<ItemType>::replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcept) {
    if (position >= 1 && position <= itemCount) {
        Node<ItemType>* nodePtr = getNodeAt(position);
        ItemType oldEntry = nodePtr->getItem();
        nodePtr->setItem(newEntry);
        return oldEntry;
    }
    throw PrecondViolatedExcept("replace() called with an empty list or invalid position.");
}

template<class ItemType>
Node<ItemType>* List<ItemType>::getNodeAt(int position) const {
    Node<ItemType>* curNodePtr = headPtr;
    for (int skip = 1; skip < position; skip++)
        curNodePtr = curNodePtr->getNext();
    return curNodePtr;
}

// Explicitly instantiated List for MonthData
template class List<MonthData>;
