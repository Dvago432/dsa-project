#ifndef SEARCHING_H
#define SEARCHING_H
#include <string>
#include "LinkedList.h"
#include "Patient.h"
#include "Ward.h"
#include "Equipment.h"
using namespace std;

// Linear search: all return the position in the list, or -1 if not found
int linearSearchPatientByID(LinkedList<Patient>& list, int id);
int linearSearchPatientByName(LinkedList<Patient>& list, string name);
int linearSearchWardByID(LinkedList<Ward>& list, int id);
int linearSearchEquipmentByID(LinkedList<Equipment>& list, int id);

// Binary search: the array MUST already be sorted by patient ID
int binarySearchPatientByID(Patient arr[], int n, int id);

#endif
