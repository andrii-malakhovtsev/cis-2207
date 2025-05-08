// Andrii Malakhovtsev
// CIS 2207 501
// 05.06.2025
// Binary Search Tree

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_

#include <stdexcept>
#include <string>

using namespace std;

class PrecondViolatedExcept : public logic_error {
public:
    PrecondViolatedExcept(const string& message = "") : logic_error("Precondition Violated Exception: " + message) {}
};
#endif