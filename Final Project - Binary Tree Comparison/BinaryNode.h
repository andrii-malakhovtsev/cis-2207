#ifndef BINARY_NODE_
#define BINARY_NODE_

#include <memory>

using namespace std;

template<class ItemType>
class BinaryNode {
private:
    ItemType item;
    shared_ptr<BinaryNode<ItemType>> leftChildPtr;
    shared_ptr<BinaryNode<ItemType>> rightChildPtr;

public:
    BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr) {}
    BinaryNode(const ItemType& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr) {}
    BinaryNode(const ItemType& anItem, shared_ptr<BinaryNode<ItemType>> leftPtr, shared_ptr<BinaryNode<ItemType>> rightPtr)
        : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {
    }

    void setItem(const ItemType& anItem) { item = anItem; }
    ItemType getItem() const { return item; }

    bool isLeaf() const { return (leftChildPtr == nullptr && rightChildPtr == nullptr); }

    auto getLeftChildPtr() const { return leftChildPtr; }
    auto getRightChildPtr() const { return rightChildPtr; }

    void setLeftChildPtr(shared_ptr<BinaryNode<ItemType>> leftPtr) { leftChildPtr = leftPtr; }
    void setRightChildPtr(shared_ptr<BinaryNode<ItemType>> rightPtr) { rightChildPtr = rightPtr; }
};
#endif