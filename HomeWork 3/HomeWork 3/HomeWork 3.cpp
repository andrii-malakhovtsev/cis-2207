// Andrii Malakhovtsev
// CIS 2207 501
// 02.16.2025
// Binary search for String

#include <iostream>
#include <string>
using namespace std;

int binarySearch(const string anArray[], int first, int last, const string& target) {
    if (first > last) {
        return -1; // Target not found
    }

    int mid = first + (last - first) / 2; // middle index

    // If the target string matches the middle element
    if (target == anArray[mid]) {
        return mid;
    }

    // If the target string is smaller, search in the left half
    else if (target < anArray[mid]) {
        return binarySearch(anArray, first, mid - 1, target);
    }
    // If the target string is greater, search in the right half
    else {
        return binarySearch(anArray, mid + 1, last, target);
    }
}

void printBinarySearchResults(string arr[], string target, int arrSize) {
    int resultIndex = binarySearch(arr, 0, arrSize - 1, target);

    cout << "Running the binary search..." << endl << endl;

    if (resultIndex != -1) {
        cout << "Found " << target << " at index " << resultIndex << " of the array" << endl;
    }
    else {
        cout << target << " not found in the array." << endl;
    }
}

int main() {
    int size;

    cout << "Enter the number of elements in the array: ";
    cin >> size;

    string* arr = new string[size];

    cout << "Enter the strings for the array (one per line):" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "Element " << (i + 1) << ": ";
        cin >> arr[i];
    }

    string target;
    cout << "Enter the string to search for:";
    cin >> target;

    printBinarySearchResults(arr, target, size);

    // Cleanup dynamically allocated memory
    delete[] arr;

    return 0;
}
