#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "BinaryNodeTree.h"
#include "NotFoundException.h"

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType> {
private:
    using BinaryNodeTree<ItemType>::rootPtr;

protected:
    shared_ptr<BinaryNode<ItemType>> placeNode(shared_ptr<BinaryNode<ItemType>> subTreePtr,
        shared_ptr<BinaryNode<ItemType>> newNodePtr) {
        if (subTreePtr == nullptr) return newNodePtr;

        if (newNodePtr->getItem() < subTreePtr->getItem()) {
            auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
            subTreePtr->setLeftChildPtr(tempPtr);
        }
        else {
            auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
            subTreePtr->setRightChildPtr(tempPtr);
        }

        return subTreePtr;
    }



    shared_ptr<BinaryNode<ItemType>> removeValue(shared_ptr<BinaryNode<ItemType>> subTreePtr,
        const ItemType target, bool& isSuccessful) {
        if (subTreePtr == nullptr) {
            isSuccessful = false;
            return subTreePtr;
        }

        if (subTreePtr->getItem() == target) {
            isSuccessful = true;

            if (subTreePtr->isLeaf()) {
                return nullptr;
            }

            if (subTreePtr->getLeftChildPtr() == nullptr) {
                return subTreePtr->getRightChildPtr();
            }

            if (subTreePtr->getRightChildPtr() == nullptr) {
                return subTreePtr->getLeftChildPtr();
            }

            ItemType inorderSuccessor;
            auto tempPtr = removeLeftmostNode(subTreePtr->getRightChildPtr(), inorderSuccessor);
            subTreePtr->setRightChildPtr(tempPtr);
            subTreePtr->setItem(inorderSuccessor);

            return subTreePtr;
        }

        if (target < subTreePtr->getItem()) {
            auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
            subTreePtr->setLeftChildPtr(tempPtr);
        }

        else {
            auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
            subTreePtr->setRightChildPtr(tempPtr);
        }

        return subTreePtr;
    }

    shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(shared_ptr<BinaryNode<ItemType>> nodePtr,
        ItemType& inorderSuccessor) {
        if (nodePtr->getLeftChildPtr() == nullptr) {
            inorderSuccessor = nodePtr->getItem();
            return nodePtr->getRightChildPtr();
        }

        nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor));

        return nodePtr;
    }

public:
    BinarySearchTree() = default;
    BinarySearchTree(const ItemType& rootItem) : BinaryNodeTree<ItemType>(rootItem) {}
    BinarySearchTree(const BinarySearchTree<ItemType>& tree) : BinaryNodeTree<ItemType>(tree) {}
    virtual ~BinarySearchTree() = default;

    bool add(const ItemType& newData) override {
        auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
        rootPtr = placeNode(rootPtr, newNodePtr);
        return true;
    }
};

#endif