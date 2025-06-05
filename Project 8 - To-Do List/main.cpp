#include "ToDoList.h"

#include <iostream>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n=== To-Do List Menu ===\n";
    cout << "1. Add Task\n";
    cout << "2. Complete (Remove) Next Task\n";
    cout << "3. Display Next Task\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int getIntegerInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input! Please, enter a number:\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

void addTask(ToDoList& list) {
    string description = getStringInput("Enter task description: ");
    int priority = getIntegerInput("Enter priority (higher number = higher priority): ");
    list.addTask(description, priority);
}

void completeTask(ToDoList& list) {
    if (list.isEmpty()) {
        cout << "Error: No tasks to complete!\n";
        return;
    }
    list.completeTask();
}

void viewNextTask(ToDoList& list) {
    if (list.isEmpty()) {
        cout << "Error: No tasks in the list!\n";
        return;
    }
    list.viewNextTask();
}

int main() {
    ToDoList myList;
    int choice = 0;

    while (true) {
        displayMenu();
        choice = getIntegerInput("");

        switch (choice) {
            case 1:
                addTask(myList);
                break;
            case 2:
                completeTask(myList);
                break;
            case 3:
                viewNextTask(myList);
                break;
            case 4:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Error: Invalid choice! Please, try again.\n";
        }
    }

    return 0;
}