#include "Rainfall.h"

#include <iostream>
#include <iomanip>

using namespace std;

bool Rainfall::monthExists(const string& month) const {
    for (int i = 1; i <= data.getLength(); i++) {
        if (data.getEntry(i).month == month) {
            return true;
        }
    }
    return false;
}

// Check if the month already exists before adding new data
void Rainfall::addMonth(const string& month, double rainfall) {
    if (monthExists(month)) {
        cout << "\nERROR: Data for " << month << " already exists. Use \'Edit\' to modify it.\n";
        return;
    }

    MonthData newData = { month, rainfall };
    data.insert(data.getLength() + 1, newData);
}

// Check if the month exists before allowing editing
void Rainfall::editMonth(const string& month, double rainfall) {
    if (!monthExists(month)) {
        cout << "\nERROR: No data available for \'" << month << "\'. Please add data first.\n";
        return;
    }

    // If month exists, find and edit the entry
    for (int i = 1; i <= data.getLength(); i++) {
        if (data.getEntry(i).month == month) {
            MonthData newData = { month, rainfall };
            data.replace(i, newData);
            cout << endl << month << " data has been updated.\n";
            return;
        }
    }
}

void Rainfall::printReport() const {
    if (data.isEmpty()) {
        cout << "\nNo data available.\n";
        return;
    }

    double total = 0;
    double maxRain = -1, minRain = -1;
    string maxMonth, minMonth;

    for (int i = 1; i <= data.getLength(); i++) {
        MonthData monthData = data.getEntry(i);
        total += monthData.rainfall;

        if (maxRain == -1 || monthData.rainfall > maxRain) {
            maxRain = monthData.rainfall;
            maxMonth = monthData.month;
        }

        if (minRain == -1 || monthData.rainfall < minRain) {
            minRain = monthData.rainfall;
            minMonth = monthData.month;
        }
    }

    double average = total / data.getLength();

    cout << "\nTotal Rainfall: " << total << " inches\n";
    cout << "Average Rainfall: " << average << " inches\n";
    cout << "Most Rainfall: " << maxMonth << " had " << maxRain << " inches\n";
    cout << "Least Rainfall: " << minMonth << " had " << minRain << " inches\n";
}
