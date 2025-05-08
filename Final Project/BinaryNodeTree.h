// Andrii Malakhovtsev
// CIS 2207 501
// 05.06.2025
// Final Project - Binary Tree Comparison

#ifndef BINARY_NODE_TREE_
#define BINARY_NODE_TREE_

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PrecondViolatedExcept.h"
#include "NotFoundException.h"

#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType> {
protected:
    shared_ptr<BinaryNode<ItemType>> rootPtr;

    int getHeightHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const {
        if (subTreePtr == nullptr) return 0;

        return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()),
            getHeightHelper(subTreePtr->getRightChildPtr()));
    }

    int getNumberOfNodesHelper(shared_ptr<BinaryNode<ItemType>> subTreePtr) const {
        if (subTreePtr == nullptr) return 0;

        return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr()) +
            getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
    }

    shared_ptr<BinaryNode<ItemType>> balancedAdd(shared_ptr<BinaryNode<ItemType>> subTreePtr,
        shared_ptr<BinaryNode<ItemType>> newNodePtr) {
        if (subTreePtr == nullptr) return newNodePtr;

        auto leftPtr = subTreePtr->getLeftChildPtr();
        auto rightPtr = subTreePtr->getRightChildPtr();

        if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr)) {
            rightPtr = balancedAdd(rightPtr, newNodePtr);
            subTreePtr->setRightChildPtr(rightPtr);
        }

        else {
            leftPtr = balancedAdd(leftPtr, newNodePtr);
            subTreePtr->setLeftChildPtr(leftPtr);
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
            return moveValuesUpTree(subTreePtr);
        }

        auto leftPtr = removeValue(subTreePtr->getLeftChildPtr(), target, isSuccessful);
        subTreePtr->setLeftChildPtr(leftPtr);

        if (!isSuccessful) {
            auto rightPtr = removeValue(subTreePtr->getRightChildPtr(), target, isSuccessful);
            subTreePtr->setRightChildPtr(rightPtr);
        }

        return subTreePtr;
    }

    shared_ptr<BinaryNode<ItemType>> moveValuesUpTree(shared_ptr<BinaryNode<ItemType>> subTreePtr) {
        if (subTreePtr->isLeaf()) return nullptr;
        if (subTreePtr->getLeftChildPtr() == nullptr) return subTreePtr->getRightChildPtr();
        if (subTreePtr->getRightChildPtr() == nullptr) return subTreePtr->getLeftChildPtr();

        ItemType inorderSuccessor;
        auto tempPtr = removeLeftmostNode(subTreePtr->getRightChildPtr(), inorderSuccessor);
        subTreePtr->setRightChildPtr(tempPtr);
        subTreePtr->setItem(inorderSuccessor);

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

    shared_ptr<BinaryNode<ItemType>> findNode(shared_ptr<BinaryNode<ItemType>> treePtr,
        const ItemType& target, bool& isSuccessful) const {
        if (treePtr == nullptr) {
            isSuccessful = false;
            return treePtr;
        }

        if (treePtr->getItem() == target) {
            isSuccessful = true;
            return treePtr;
        }

        auto foundPtr = findNode(treePtr->getLeftChildPtr(), target, isSuccessful);
        if (!isSuccessful) {
            foundPtr = findNode(treePtr->getRightChildPtr(), target, isSuccessful);
        }

        return foundPtr;
    }

    shared_ptr<BinaryNode<ItemType>> copyTree(const shared_ptr<BinaryNode<ItemType>> oldTreeRootPtr) const {
        if (oldTreeRootPtr == nullptr) return nullptr;

        auto newTreePtr = make_shared<BinaryNode<ItemType>>(oldTreeRootPtr->getItem());
        newTreePtr->setLeftChildPtr(copyTree(oldTreeRootPtr->getLeftChildPtr()));
        newTreePtr->setRightChildPtr(copyTree(oldTreeRootPtr->getRightChildPtr()));
        return newTreePtr;
    }

    void destroyTree(shared_ptr<BinaryNode<ItemType>> subTreePtr) {
        if (subTreePtr != nullptr) {
            destroyTree(subTreePtr->getLeftChildPtr());
            destroyTree(subTreePtr->getRightChildPtr());
            subTreePtr.reset();
        }
    }

    void preorder(std::function<void(ItemType&)> visit,
        shared_ptr<BinaryNode<ItemType>> treePtr) const {
        if (treePtr != nullptr) {
            ItemType theItem = treePtr->getItem();
            visit(theItem);
            preorder(visit, treePtr->getLeftChildPtr());
            preorder(visit, treePtr->getRightChildPtr());
        }
    }

    void inorder(std::function<void(ItemType&)> visit,
        shared_ptr<BinaryNode<ItemType>> treePtr) const {
        if (treePtr != nullptr) {
            inorder(visit, treePtr->getLeftChildPtr());
            ItemType theItem = treePtr->getItem();
            visit(theItem);
            inorder(visit, treePtr->getRightChildPtr());
        }
    }

    void postorder(std::function<void(ItemType&)> visit,
        shared_ptr<BinaryNode<ItemType>> treePtr) const {
        if (treePtr != nullptr) {
            postorder(visit, treePtr->getLeftChildPtr());
            postorder(visit, treePtr->getRightChildPtr());
            ItemType theItem = treePtr->getItem();
            visit(theItem);
        }
    }

public:
    BinaryNodeTree() : rootPtr(nullptr) {}
    BinaryNodeTree(const ItemType& rootItem) {
        rootPtr = make_shared<BinaryNode<ItemType>>(rootItem, nullptr, nullptr);
    }
    BinaryNodeTree(const ItemType& rootItem,
        shared_ptr<BinaryNode<ItemType>> leftTreePtr,
        shared_ptr<BinaryNode<ItemType>> rightTreePtr) {
        rootPtr = make_shared<BinaryNode<ItemType>>(rootItem,
            copyTree(leftTreePtr),
            copyTree(rightTreePtr));
    }
    BinaryNodeTree(const shared_ptr<BinaryNode<ItemType>> tree) {
        rootPtr = copyTree(tree);
    }
    virtual ~BinaryNodeTree() {
        destroyTree(rootPtr);
    }

    bool isEmpty() const override {
        return rootPtr == nullptr;
    }

    int getHeight() const override {
        return getHeightHelper(rootPtr);
    }

    int getNumberOfNodes() const override {
        return getNumberOfNodesHelper(rootPtr);
    }

    ItemType getRootData() const throw(PrecondViolatedExcept)override {
        if (isEmpty()) throw PrecondViolatedExcept("getRootData() called with empty tree.");
        return rootPtr->getItem();
    }

    void setRootData(const ItemType& newData) override {
        if (isEmpty()) {
            rootPtr = make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
        }

        else {
            rootPtr->setItem(newData);
        }
    }

    virtual bool add(const ItemType& newData) override {
        auto newNodePtr = make_shared<BinaryNode<ItemType>>(newData);
        rootPtr = balancedAdd(rootPtr, newNodePtr);

        return true;
    }

    bool remove(const ItemType& data) override {
        bool isSuccessful = false;
        rootPtr = removeValue(rootPtr, data, isSuccessful);

        return isSuccessful;
    }

    void clear() override {
        destroyTree(rootPtr);
        rootPtr.reset();
    }

    ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException)override {
        bool isSuccessful = false;
        auto foundPtr = findNode(rootPtr, anEntry, isSuccessful);

        if (isSuccessful) return foundPtr->getItem();

        throw NotFoundException("Entry not found in tree.");
    }

    bool contains(const ItemType& anEntry) const override {
        bool isSuccessful = false;
        findNode(rootPtr, anEntry, isSuccessful);

        return isSuccessful;
    }

    void preorderTraverse(std::function<void(ItemType&)> visit) const override {
        preorder(visit, rootPtr);
    }

    void inorderTraverse(std::function<void(ItemType&)> visit) const override {
        inorder(visit, rootPtr);
    }

    void postorderTraverse(std::function<void(ItemType&)> visit) const override {
        postorder(visit, rootPtr);
    }

    BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide) {
        if (this != &rightHandSide) {
            destroyTree(rootPtr);
            rootPtr = copyTree(rightHandSide.rootPtr);
        }
        return *this;
    }

    bool isSameTree(const BinaryNodeTree<ItemType>& otherTree) const {
        vector<ItemType> thisItems, otherItems;

        auto collector = [](vector<ItemType>& items) {
            return [&items](ItemType& item) { items.push_back(item); };
            };

        this->inorderTraverse(collector(thisItems));
        otherTree.inorderTraverse(collector(otherItems));

        // Sort for general binary trees
        sort(thisItems.begin(), thisItems.end());
        sort(otherItems.begin(), otherItems.end());

        return thisItems == otherItems;
    }
};

#endif 