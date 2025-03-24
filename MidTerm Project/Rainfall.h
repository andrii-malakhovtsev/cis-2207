// Andrii Malakhovtsev
// CIS 2207 501
// 03.23.2025
// MidTerm Project - Rainfall Statistics

#ifndef RAINFALL_H
#define RAINFALL_H

#include "List.h"
#include "MonthData.h"
#include <string>
#include <iostream>
using namespace std;

class Rainfall {
public:
    void addMonth(const string& month, double rainfall);
    void editMonth(const string& month, double rainfall);
    void printReport() const;

private:
    List<MonthData> data;

    bool monthExists(const string& month) const;
};

#endif
