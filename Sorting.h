#ifndef SORTING_H
#define SORTING_H
#include "LinkedList.h"
#include "Patient.h"
using namespace std;

// sort criteria
const int BY_ID = 1;
const int BY_NAME = 2;
const int BY_DATE = 3;
const int BY_PRIORITY = 4; //1 (Emergency) comes first

// counts comparisons so the two sorts can be compared
extern long sortComparisons;

// copies the linked list into a new array (remember delete[] when done)
Patient* listToArray(LinkedList<Patient>& list, int& n);

void insertionSort(Patient arr[], int n, int criteria);
void mergeSort(Patient arr[], int left, int right, int criteria);

#endif