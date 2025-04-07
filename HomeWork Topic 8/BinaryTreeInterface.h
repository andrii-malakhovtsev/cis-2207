// Andrii Malakhovtsev
// CIS 2207 501
// 04.06.2025
// Binary Search Tree

#ifndef BINARY_TREE_INTERFACE_
#define BINARY_TREE_INTERFACE_

#include "NotFoundException.h"
#include <functional>

template<class ItemType>
class BinaryTreeInterface {
public:
    virtual ~BinaryTreeInterface() = default;

    virtual bool isEmpty() const = 0;
    virtual int getHeight() const = 0;
    virtual int getNumberOfNodes() const = 0;
    virtual ItemType getRootData() const = 0;
    virtual void setRootData(const ItemType& newData) = 0;
    virtual bool add(const ItemType& newData) = 0;
    virtual bool remove(const ItemType& target) = 0;
    virtual void clear() = 0;
    virtual ItemType getEntry(const ItemType& target) const = 0;
    virtual bool contains(const ItemType& target) const = 0;

    virtual void preorderTraverse(std::function<void(ItemType&)> visit) const = 0;
    virtual void inorderTraverse(std::function<void(ItemType&)> visit) const = 0;
    virtual void postorderTraverse(std::function<void(ItemType&)> visit) const = 0;
};

#endif