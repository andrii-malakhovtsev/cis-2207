#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX_SIZE = 25000;

// Selection Sort
template <class ItemType>
int findIndexOfLargest(const ItemType theArray[], int size)
{
    int indexSoFar = 0;
    for (int currentIndex = 1; currentIndex < size; currentIndex++)
    {
        if (theArray[currentIndex] > theArray[indexSoFar])
            indexSoFar = currentIndex;
    }
    return indexSoFar;
}

template <class ItemType>
void selectionSort(ItemType theArray[], int n) {
    for (int last = n - 1; last >= 1; last--) {
        int largest = findIndexOfLargest(theArray, last + 1);

        swap(theArray[largest], theArray[last]);
    }
}

// Bubble Sort
template <class ItemType>
void bubbleSort(ItemType theArray[], int n) 
{
    bool sorted = false;
    int pass = 1;
    while (!sorted && (pass < n))
    {
        sorted = true;
        for (int index = 0; index < n - pass; index++)
        {
            int nextIndex = index + 1;
            if (theArray[index] > theArray[nextIndex]) 
            {
                swap(theArray[index], theArray[nextIndex]);
                sorted = false;
            }
        }
    }
}

// Insertion Sort
template <class ItemType>
void insertionSort(ItemType theArray[], int n) 
{
    for (int unsorted = 1; unsorted < n; unsorted++)
    {
        ItemType nextItem = theArray[unsorted];
        int loc = unsorted;
        while ((loc > 0) && (theArray[loc - 1] > nextItem)) 
        {
            theArray[loc] = theArray[loc - 1];
            loc--;
        }
        theArray[loc] = nextItem;
    }
}

// Merge Sort
template <class ItemType>
void merge(ItemType theArray[], int first, int mid, int last) 
{
    ItemType tempArray[MAX_SIZE];

    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;

    int index = first1;
    while ((first1 <= last1) && (first2 <= last2)) 
    {
        if (theArray[first1] <= theArray[first2])
        {
            tempArray[index] = theArray[first1];
            first1++;
        }
        else
        {
            tempArray[index] = theArray[first2];
            first2++;
        }
        index++;
    }
    while (first1 <= last1)
    {
        tempArray[index] = theArray[first1];
        first1++;
        index++;
    }
    while (first2 <= last2)
    {
        tempArray[index] = theArray[first2];
        first2++;
        index++;
    }

    for (index = first; index <= last; index++)
        theArray[index] = tempArray[index];
}

template<class ItemType>
void mergeSort(ItemType theArray[], int first, int last) 
{
    if (first < last)
    {
        int mid = first + (last - first) / 2;

        mergeSort(theArray, first, mid);

        mergeSort(theArray, mid + 1, last);

        merge(theArray, first, mid, last);
    }
}

// Quick Sort
template <class ItemType>
int partition(ItemType theArray[], int first, int last) {
    ItemType pivot = theArray[last];
    int i = first - 1;
    for (int j = first; j < last; j++) {
        if (theArray[j] <= pivot)
            swap(theArray[++i], theArray[j]);
    }
    swap(theArray[i + 1], theArray[last]);
    return i + 1;
}

template<class ItemType>
void insertionSort2(ItemType theArray[], int first, int last) {
    for (int unsorted = first + 1; unsorted <= last; unsorted++) {
        ItemType nextItem = theArray[unsorted];
        int loc = unsorted;
        while ((loc > first) && (theArray[loc - 1] > nextItem)) {
            theArray[loc] = theArray[loc - 1];
            loc--;
        }
        theArray[loc] = nextItem;
    }
}

template <class ItemType>
void quickSort(ItemType theArray[], int first, int last)
{
    if ((last - first + 1) < 10)
    {
        insertionSort2(theArray, first, last);
    }
    else
    {
        int pivotIndex = partition(theArray, first, last);

        quickSort(theArray, first, pivotIndex - 1);
        quickSort(theArray, pivotIndex + 1, last);
    }
}

// Radix Sort
template <class ItemType>
int getMaxDigits(ItemType theArray[], int n) {
    int maxVal = *max_element(theArray, theArray + n);
    int digits = 0;
    while (maxVal > 0) {
        digits++;
        maxVal /= 10;
    }
    return digits;
}

int getDigit(int number, int d) {
    return (number / static_cast<int>(pow(10, d))) % 10;
}

template <class ItemType>
void radixSort(ItemType theArray[], int n) {
    int maxDigits = getMaxDigits(theArray, n);

    for (int j = 0; j < maxDigits; j++) {
        vector<vector<ItemType>> buckets(10);

        for (int i = 0; i < n; i++) {
            int k = getDigit(theArray[i], j);
            buckets[k].push_back(theArray[i]);
        }

        int index = 0;
        for (int k = 0; k < 10; k++) {
            for (ItemType num : buckets[k]) {
                theArray[index++] = num;
            }
        }
    }
}

// Function to measure sorting time
template <class SortFunc>
void timeSorting(SortFunc sortFunc, int arr[], int n, const string& sortName) {
    clock_t start = clock();
    sortFunc(arr, n);
    clock_t end = clock();
    cout << "  " << sortName << " took " << double(end - start) / CLOCKS_PER_SEC << " seconds." << endl;
}

template <class SortFunc>
void timeSorting(SortFunc sortFunc, int arr[], int first, int last, const string& sortName) {
    clock_t start = clock();
    sortFunc(arr, first, last);
    clock_t end = clock();
    cout << "  " << sortName << " took " << double(end - start) / CLOCKS_PER_SEC << " seconds." << endl;
}

int main() {
    srand(time(0));
    vector<int> sizes = { 1000, 5000, 10000, 20000 };
    for (int size : sizes) {
        int* arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = rand() % 100000;

        int* copy = new int[size];

        cout << size << " items Array:" << endl;

        memcpy(copy, arr, size * sizeof(int));
        timeSorting(selectionSort<int>, copy, size, "Selection Sort");

        memcpy(copy, arr, size * sizeof(int));
        timeSorting(bubbleSort<int>, copy, size, "Bubble Sort");

        memcpy(copy, arr, size * sizeof(int));
        timeSorting(insertionSort<int>, copy, size, "Insertion Sort");

        memcpy(copy, arr, size * sizeof(int));
        timeSorting(mergeSort<int>, copy, 0, size - 1, "Merge Sort");

        memcpy(copy, arr, size * sizeof(int));
        timeSorting(quickSort<int>, copy, 0, size - 1, "Quick Sort");

        delete[] arr;
        delete[] copy;

        cout << endl;
    }
    return 0;
}
