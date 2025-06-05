#ifndef ARRAY_MAX_HEAP_
#define ARRAY_MAX_HEAP_

#include <memory>

#include "HeapInterface.h"
#include "PrecondViolatedExcept.h"
#include "Task.h"

using namespace std;

template<class ItemType>
class ArrayMaxHeap : public HeapInterface<ItemType>
{
private:
    static const int ROOT_INDEX = 0;
    static const int DEFAULT_CAPACITY = 21;
    unique_ptr<ItemType[]> items;
    int itemCount;
    int maxItems;

    int getLeftChildIndex(const int nodeIndex) const;
    int getRightChildIndex(int nodeIndex) const;
    int getParentIndex(int nodeIndex) const;
    bool isLeaf(int nodeIndex) const;
    void heapRebuild(int nodeIndex);
    void heapCreate();

public:
    ArrayMaxHeap();
    ArrayMaxHeap(const ItemType someArray[], const int arraySize);
    virtual ~ArrayMaxHeap();

    bool isEmpty() const;
    int getNumberOfNodes() const;
    int getHeight() const;
    ItemType peekTop() const throw(PrecondViolatedExcept);
    bool add(const ItemType& newData);
    bool remove();
    void clear();
};

template class ArrayMaxHeap<Task>;
#endif