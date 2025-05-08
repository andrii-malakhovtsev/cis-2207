// Andrii Malakhovtsev
// CIS 2207 501
// 04.13.2025
// To-Do List

#ifndef PRIORITY_QUEUE_INTERFACE_
#define PRIORITY_QUEUE_INTERFACE_

template<class ItemType>
class PriorityQueueInterface
{
public:
    virtual bool isEmpty() const = 0;
    virtual bool enqueue(const ItemType& newEntry) = 0;
    virtual bool dequeue() = 0;
    virtual ItemType peekFront() const = 0;
    virtual ~PriorityQueueInterface() {}
};
#endif