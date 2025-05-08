// Andrii Malakhovtsev
// CIS 2207 501
// 05.06.2025
// Final Project - Binary Tree Comparison

#ifndef NOT_FOUND_EXCEPTION_
#define NOT_FOUND_EXCEPTION_

#include <stdexcept>
#include <string>

using namespace std;

class NotFoundException : public exception {
private:
    string message;

public:
    NotFoundException(const string& msg = "") : message(msg) {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
};
#endif