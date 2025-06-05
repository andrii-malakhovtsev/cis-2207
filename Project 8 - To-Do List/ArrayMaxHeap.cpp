#include "ArrayMaxHeap.h"

#include <algorithm>
#include <cmath>

using namespace std;

template<class ItemType>
int ArrayMaxHeap<ItemType>::getLeftChildIndex(const int nodeIndex) const
{
    return (2 * nodeIndex) + 1;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getRightChildIndex(int nodeIndex) const
{
    return (2 * nodeIndex) + 2;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getParentIndex(int nodeIndex) const
{
    return (nodeIndex - 1) / 2;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isLeaf(int nodeIndex) const
{
    return (getLeftChildIndex(nodeIndex) >= itemCount);
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int nodeIndex)
{
    if (!isLeaf(nodeIndex))
    {
        int leftChildIndex = getLeftChildIndex(nodeIndex);
        int largerChildIndex = leftChildIndex;
        int rightChildIndex = getRightChildIndex(nodeIndex);

        if (rightChildIndex < itemCount)
        {
            if (items[rightChildIndex] > items[leftChildIndex])
                largerChildIndex = rightChildIndex;
        }

        if (items[nodeIndex] < items[largerChildIndex])
        {
            swap(items[nodeIndex], items[largerChildIndex]);
            heapRebuild(largerChildIndex);
        }
    }
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::heapCreate()
{
    for (int index = itemCount / 2 - 1; index >= 0; index--)
        heapRebuild(index);
}

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
    items = make_unique<ItemType[]>(maxItems);
}

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ItemType someArray[], const int arraySize)
    : itemCount(arraySize), maxItems(2 * arraySize)
{
    items = make_unique<ItemType[]>(maxItems);

    for (int i = 0; i < itemCount; i++)
        items[i] = someArray[i];

    heapCreate();
}

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
    clear();
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
    return itemCount == 0;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
    return itemCount;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
    return ceil(log2(itemCount + 1));
}

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const throw(PrecondViolatedExcept)
{
    if (isEmpty())
        throw PrecondViolatedExcept("Attempted peek into an empty heap.");

    return items[ROOT_INDEX];
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
{
    if (itemCount >= maxItems)
        return false;

    items[itemCount] = newData;

    int newDataIndex = itemCount;
    bool inPlace = false;

    while ((newDataIndex > 0) && !inPlace)
    {
        int parentIndex = getParentIndex(newDataIndex);

        if (items[newDataIndex] < items[parentIndex])
            inPlace = true;
        else
        {
            swap(items[newDataIndex], items[parentIndex]);
            newDataIndex = parentIndex;
        }
    }

    itemCount++;
    return true;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
    if (isEmpty())
        return false;

    items[ROOT_INDEX] = items[itemCount - 1];
    itemCount--;
    heapRebuild(ROOT_INDEX);

    return true;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
    itemCount = 0;
}