#ifndef TASK_
#define TASK_

#include <string>
#include <iostream>

using namespace std;

class Task
{
private:
    string description;
    int priority;  // Higher numbers mean higher priority

public:
    Task();
    Task(const string& taskDescription, int taskPriority);

    bool operator<(const Task& other) const;
    bool operator>(const Task& other) const;

    string getDescription() const;
    int getPriority() const;

    friend ostream& operator<<(ostream& os, const Task& item);
};

#endif