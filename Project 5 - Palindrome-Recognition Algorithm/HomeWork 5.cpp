#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"

using namespace std;

bool isPalindrome(const string& someString);

int main() {
	string testString;

	while (true) {
		cout << "Enter a string to check if it's a palindrome (or type 'exit' to quit): ";
		getline(cin, testString);

		if (testString == "exit") {
			cout << "Exiting program..." << endl;
			break;
		}

		if (isPalindrome(testString)) {
			cout << endl << "\"" << testString << "\" is a palindrome." << endl << endl;
		}
		else {
			cout << endl << "\"" << testString << "\" is not a palindrome." << endl << endl;
		}
	}

	return 0;
}

bool isPalindrome(const string& someString) {
	Queue<char> aQueue;
	Stack<char> aStack;

	for (char ch : someString) {
		aQueue.enqueue(ch);
		aStack.push(ch);
	}

	bool charactersAreEqual = true;
	while (!aQueue.isEmpty() && charactersAreEqual) {
		char queueFront = aQueue.peekFront();
		char stackTop = aStack.peek();
		if (queueFront == stackTop) {
			aQueue.dequeue();
			aStack.pop();
		}
		else {
			charactersAreEqual = false;
		}
	}

	return charactersAreEqual;
}
