// Andrii Malakhovtsev
// CIS 2207 501
// 03.30.2025
// Array Dictionary

#ifndef PRECOND_VIOLATED_EXCEPT_H
#define PRECOND_VIOLATED_EXCEPT_H

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public exception {
private:
    string message;

public:
    PrecondViolatedExcept(const string& msg = "") : message(msg) {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
};

#endif