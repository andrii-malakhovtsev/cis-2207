#ifndef PRECOND_VIOLATED_EXCEPT_H
#define PRECOND_VIOLATED_EXCEPT_H

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public logic_error {
public:
    PrecondViolatedExcept(const string& message = "") : logic_error("Precondition Violated Exception: " + message) {}
};

#endif