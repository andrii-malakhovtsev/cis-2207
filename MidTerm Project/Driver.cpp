// Andrii Malakhovtsev
// CIS 2207 501
// 03.23.2025
// MidTerm Project - Rainfall Statistics

#include "Rainfall.h"

#include <iostream>
#include <cctype>

using namespace std;

static void displayMenu();

int main() {
    char choice;
    string month;
    double rainfall;
    Rainfall rainfallStats;

    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice) {
        case 'A':
            cout << "Enter Month: ";
            cin >> month;
            cout << "Enter Rainfall (in Inches): ";
            cin >> rainfall;
            rainfallStats.addMonth(month, rainfall);
            break;
        case 'E':
            cout << "Enter Month: ";
            cin >> month;
            cout << "Enter Rainfall (in Inches): ";
            cin >> rainfall;
            rainfallStats.editMonth(month, rainfall);
            break;
        case 'P':
            rainfallStats.printReport();
            break;
        case 'Q':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
        cout << endl;
    } while (choice != 'Q');

    return 0;
}

static void displayMenu() {
    cout << "A -- Add a month of statistics\n";
    cout << "E -- Edit a month of statistics\n";
    cout << "P -- Print report\n";
    cout << "Q -- Quit\n";
}
