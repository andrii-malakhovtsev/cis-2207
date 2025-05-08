// Andrii Malakhovtsev
// CIS 2207 501
// 04.13.2025
// To-Do List

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public logic_error
{
public:
    PrecondViolatedExcept(const string& message = "")
        : logic_error("Error: Precondition Violated Exception: " + message) {
    }
};

#endif