#ifndef HEAP_PRIORITY_QUEUE_
#define HEAP_PRIORITY_QUEUE_

#include "ArrayMaxHeap.h"
#include "PriorityQueueInterface.h"

using namespace std;

template<class ItemType>
class HeapPriorityQueue : public PriorityQueueInterface<ItemType>, private ArrayMaxHeap<ItemType>
{
public:
    HeapPriorityQueue();
    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    ItemType peekFront() const throw(PrecondViolatedExcept);
   
};

template class HeapPriorityQueue<Task>;
#endif