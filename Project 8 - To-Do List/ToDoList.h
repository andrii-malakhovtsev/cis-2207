#ifndef TODO_LIST_
#define TODO_LIST_

#include "HeapPriorityQueue.h"
#include "Task.h"

using namespace std;

class ToDoList
{
private:
    HeapPriorityQueue<Task> tasks;

public:
    void addTask(const string& description, int priority);
    void completeTask();
    void viewNextTask() const;
    bool isEmpty() const;
};

#endif