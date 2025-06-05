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
