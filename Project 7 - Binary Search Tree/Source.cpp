#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include "BinarySearchTree.h"
#include "Person.h"

using namespace std;

class Source {
private:
    BinarySearchTree<Person> bst;

    static void printPerson(Person& person) {
        cout << person << endl;
    }

    class SaveVisitor {
    private:
        ofstream& outFile;
    public:
        SaveVisitor(ofstream& file) : outFile(file) {}
        void operator()(Person& person) {
            outFile << person.getName() << "," << person.getBirthday() << "\n";
        }
    };

    class MonthVisitor {
    private:
        vector<Person>& matches;
        string formattedMonth;
    public:
        MonthVisitor(vector<Person>& m, const string& month)
            : matches(m), formattedMonth(month) {
        }
        void operator()(Person& person) {
            if (person.getBirthday().substr(0, 2) == formattedMonth) {
                matches.push_back(person);
            }
        }
    };

public:
    void enterPerson() {
        string name, birthday;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter birthday [MM/DD/YYYY]: ";
        getline(cin, birthday);

        Person newPerson(name, birthday);
        if (bst.add(newPerson)) {
            cout << "Person added successfully.\n";
        }
        else {
            cout << "Person already exists in the database.\n";
        }
    }

    void modifyPerson() {
        string name;
        cout << "Enter the name of the person to modify: ";
        getline(cin, name);

        try {
            Person toFind(name, "");
            Person foundPerson = bst.getEntry(toFind);

            cout << "Current data: " << foundPerson << endl;
            cout << "Enter new name (or press Enter to keep current): ";
            string newName;
            getline(cin, newName);

            cout << "Enter new birthday [MM/DD/YYYY] (or press Enter to keep current): ";
            string newBirthday;
            getline(cin, newBirthday);

            bst.remove(foundPerson);

            if (!newName.empty()) foundPerson.setName(newName);
            if (!newBirthday.empty()) foundPerson.setBirthday(newBirthday);

            bst.add(foundPerson);
            cout << "Person modified successfully.\n";
        }
        catch (NotFoundException&) {
            cout << "Person not found in database.\n";
        }
    }

    void removePerson() {
        string name;
        cout << "Enter name of person to remove: ";
        getline(cin, name);

        Person toRemove(name, "");
        if (bst.remove(toRemove)) {
            cout << "Person removed successfully.\n";
        }
        else {
            cout << "Person not found in database.\n";
        }
    }

    void searchPerson() {
        string name;
        cout << "Enter name to search: ";
        getline(cin, name);

        try {
            Person toFind(name, "");
            Person foundPerson = bst.getEntry(toFind);
            cout << "Found: " << foundPerson << endl;
        }
        catch (NotFoundException&) {
            cout << "Person not found in database.\n";
        }
    }

    void queryByMonth() {
        string monthStr;
        cout << "Enter month (1-12) to query: ";
        getline(cin, monthStr);
        int month;

        try {
            month = stoi(monthStr);
            if (month < 1 || month > 12) throw out_of_range("Invalid month");
        }
        catch (...) {
            cout << "Invalid month entered.\n";
            return;
        }

        string formattedMonth = (month < 10) ? "0" + to_string(month) : to_string(month);
        vector<Person> matches;

        MonthVisitor visitor(matches, formattedMonth);
        bst.inorderTraverse(visitor);

        if (matches.empty()) {
            cout << "No birthdays found in this month " << month << ".\n";
        }
        else {
            cout << "Birthdays in a specific month " << month << ":\n";
            for (const auto& person : matches) {
                cout << person << endl;
            }
        }
    }

    void printAll() {
        if (bst.isEmpty()) {
            cout << "Database is empty.\n";
            return;
        }

        cout << "=== All people in the database ===\n";
        bst.inorderTraverse(printPerson);
    }
};

void displayMenu() {
    cout << "\Birth Database Menu:\n";
    cout << "1. Enter a new person\n";
    cout << "2. Modify person's data\n";
    cout << "3. Remove a person\n";
    cout << "4. Search for a person\n";
    cout << "5. Query by birth month\n";
    cout << "6. Print all people\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    const int EXIT_CHOICE = 7;

    Source database;
    string filename;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore();

        cout << endl;

        switch (choice) {
        case 1: database.enterPerson(); break;
        case 2: database.modifyPerson(); break;
        case 3: database.removePerson(); break;
        case 4: database.searchPerson(); break;
        case 5: database.queryByMonth(); break;
        case 6: database.printAll(); break;
        case EXIT_CHOICE: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (choice != EXIT_CHOICE);

    return 0;
} 