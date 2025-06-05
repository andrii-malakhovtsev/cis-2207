#include "ToDoList.h"

#include <iostream>

using namespace std;

void ToDoList::addTask(const string& description, int priority)
{
    tasks.enqueue(Task(description, priority));
    cout << "Added task: " << description << " with priority " << priority << endl;
}

void ToDoList::completeTask()
{
    if (isEmpty())
    {
        cout << "No tasks to complete!" << endl;
        return;
    }

    cout << "Completed task: " << tasks.peekFront().getDescription() << endl;
    tasks.dequeue();
}

void ToDoList::viewNextTask() const
{
    if (isEmpty())
    {
        cout << "No tasks in the list!" << endl;
        return;
    }

    cout << "Next task: " << tasks.peekFront() << endl;
}

bool ToDoList::isEmpty() const
{
    return tasks.isEmpty();
}