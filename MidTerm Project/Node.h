// Andrii Malakhovtsev
// CIS 2207 501
// 03.23.2025
// MidTerm Project - Rainfall Statistics

#ifndef NODE_H
#define NODE_H

template<class ItemType>
class Node {
private:
    ItemType item;
    Node<ItemType>* next;

public:
    Node() : next(nullptr) {}
    Node(const ItemType& anItem) : item(anItem), next(nullptr) {}
    Node(const ItemType& anItem, Node<ItemType>* nextNode) : item(anItem), next(nextNode) {}

    void setItem(const ItemType& anItem) { item = anItem; }
    void setNext(Node<ItemType>* nextNode) { next = nextNode; }

    ItemType getItem() const { return item; }
    Node<ItemType>* getNext() const { return next; }
};

#endif
