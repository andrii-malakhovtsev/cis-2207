// Andrii Malakhovtsev
// CIS 2207 501
// 03.30.2025
// Array Dictionary

#include "ArrayDictionary.h"

#include <iostream>
#include <string>
#include <limits> // input validation

using namespace std;

void printValue();
void displayMenu();
void handleAdd(ArrayDictionary<string, string>& dict);
void handleRemove(ArrayDictionary<string, string>& dict);
void handleLookup(ArrayDictionary<string, string>& dict);
void handleContains(ArrayDictionary<string, string>& dict);
void handleDisplayAll(ArrayDictionary<string, string>& dict);
void clearInputBuffer();

const int FIRST_CHOICE = 1, LAST_CHOICE = 8;

int main() {
    ArrayDictionary<string, string> dictionary;
    int choice = 0;

    cout << "==== Dictionary Test Program ====" << endl;

    while (true) {
        displayMenu();

        // Input validation
        while (!(cin >> choice) || choice < FIRST_CHOICE || choice > LAST_CHOICE) {
            cout << "Invalid input. Please enter a number between " << FIRST_CHOICE << " and " << LAST_CHOICE << ": ";
            clearInputBuffer();
        }
        // Clear the newline character
        clearInputBuffer();

        switch (choice) {
        case FIRST_CHOICE:
            handleAdd(dictionary);
            break;
        case 2:
            handleRemove(dictionary);
            break;
        case 3:
            handleLookup(dictionary);
            break;
        case 4:
            handleContains(dictionary);
            break;
        case 5:
            handleDisplayAll(dictionary);
            break;
        case 6:
            cout << "Number of entries: " << dictionary.getNumberOfEntries() << endl;
            break;
        case 7:
            dictionary.clear();
            cout << "Dictionary cleared!" << endl;
            break;
        case LAST_CHOICE:
            cout << "Exiting program..." << endl;
            return 0;
        default:
            cout << "Error: Invalid choice!" << endl;
        }
    }

    return 0;
}

void printValue(string& value) {
    cout << "Value: " << value << endl;
}

void displayMenu() {
    cout << "\n===== Dictionary Menu =====" << endl;
    cout << FIRST_CHOICE << ". Add an entry" << endl;
    cout << "2. Remove an entry" << endl;
    cout << "3. Look up a value" << endl;
    cout << "4. Check if the key exists" << endl;
    cout << "5. Display all entries" << endl;
    cout << "6. Get the number of entries" << endl;
    cout << "7. Clear the dictionary" << endl;
    cout << LAST_CHOICE << ". Exit" << endl;
    cout << "==========================" << endl;
    cout << "Enter your choice (1-8): ";
}

void handleAdd(ArrayDictionary<string, string>& dict) {
    string key, value;
    cout << "Enter key: ";
    getline(cin, key);
    cout << "Enter value: ";
    getline(cin, value);

    try {
        if (dict.add(key, value)) {
            cout << "Entry added successfully!" << endl;
        }
        else {
            cout << "Error: Dictionary is full, cannot add more entries." << endl;
        }
    }
    catch (const PrecondViolatedExcept& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void handleRemove(ArrayDictionary<string, string>& dict) {
    string key;
    cout << "Enter key to remove: ";
    getline(cin, key);

    if (dict.remove(key)) {
        cout << "Entry removed successfully!" << endl;
    }
    else {
        cout << "Error: Key not found!" << endl;
    }
}

void handleLookup(ArrayDictionary<string, string>& dict) {
    string key;
    cout << "Enter key to look up: ";
    getline(cin, key);

    try {
        string value = dict.getValue(key);
        cout << "Value found: " << value << endl;
    }
    catch (const NotFoundException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void handleContains(ArrayDictionary<string, string>& dict) {
    string key;
    cout << "Enter key to check: ";
    getline(cin, key);

    cout << "Key " << (dict.contains(key) ? "exists" : "does not exist") << " in the dictionary" << endl;
}

void handleDisplayAll(ArrayDictionary<string, string>& dict) {
    cout << "\n=== All Dictionary Entries ===" << endl;
    if (dict.isEmpty()) {
        cout << "Dictionary is empty!" << endl;
    }
    else {
        dict.traverse(printValue);
    }
    cout << "============================" << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
