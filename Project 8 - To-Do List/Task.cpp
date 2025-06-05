#include "Task.h"

Task::Task() : description(""), priority(0) {}

Task::Task(const string& taskDescription, int taskPriority)
    : description(taskDescription), priority(taskPriority) {}

bool Task::operator<(const Task& other) const
{
    return priority < other.priority;
}

bool Task::operator>(const Task& other) const
{
    return priority > other.priority;
}

string Task::getDescription() const
{
    return description;
}

int Task::getPriority() const
{
    return priority;
}

ostream& operator<<(ostream& os, const Task& item)
{
    os << "[" << item.priority << "] " << item.description;
    return os;
}