#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <vector>
#include <ctime>
#include <iostream>

void selectionSort(std::vector<int>& arr);
void bubbleSort(std::vector<int>& arr);
void insertionSort(std::vector<int>& arr);
void mergeSort(std::vector<int>& arr);
void quickSort(std::vector<int>& arr, int low, int high);
void printTimingResults(int numItems);

#endif
