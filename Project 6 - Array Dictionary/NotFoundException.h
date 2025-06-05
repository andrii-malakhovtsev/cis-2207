#ifndef NOT_FOUND_EXCEPTION_H
#define NOT_FOUND_EXCEPTION_H

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