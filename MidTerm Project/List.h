// Andrii Malakhovtsev
// CIS 2207 501
// 03.23.2025
// MidTerm Project - Rainfall Statistics

#ifndef LIST_H
#define LIST_H

#include <string>
#include "Node.h"
#include "PrecondViolatedExcept.h"

using namespace std;

template<class ItemType>
class List {
private:
    Node<ItemType>* headPtr;
    int itemCount;

    Node<ItemType>* getNodeAt(int position) const;

public:
    List();
    List(const List<ItemType>& aList);
    virtual ~List();

    bool isEmpty() const;
    int getLength() const;
    bool insert(int newPosition, const ItemType& newEntry);
    bool remove(int position);
    void clear();

    ItemType getEntry(int position) const throw(PrecondViolatedExcept);
    ItemType replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcept);
};

#endif
