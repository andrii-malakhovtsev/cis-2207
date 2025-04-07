// Andrii Malakhovtsev
// CIS 2207 501
// 04.06.2025
// Binary Search Tree

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