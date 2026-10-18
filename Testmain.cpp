// Quick test of Student A's modules (replace with the real main.cpp later)
#include <iostream>
#include "LinkedList.h"
#include "Patient.h"
#include "Ward.h"
#include "Equipment.h"
#include "Searching.h"
#include "Sorting.h"
#include "FileManager.h"
using namespace std;

int main(){

	LinkedList<Patient> patients;
	LinkedList<Ward> wards;
	LinkedList<Equipment> equipment;

	// linked list operations
	patients.insertEnd(Patient(305, "Thabo", 30, "Fever", "Ward A", 12, 3, 2026, "Admitted", 3));
	patients.insertEnd(Patient(101, "Mpho", 45, "Fracture", "Ward B", 5, 1, 2026, "Admitted", 2));
	patients.insertFront(Patient(220, "Lerato", 27, "Malaria", "Ward A", 20, 2, 2026, "Waiting", 1));
	patients.insertAt(1, Patient(150, "Neo", 60, "Asthma", "Ward C", 1, 4, 2026, "Admitted", 4));
	cout << "Patients (" << patients.getSize() << "):" << endl;
	for(int i = 0; i < patients.getSize(); i++){
		patients.getAt(i)->display();
	}

	patients.deleteAt(2);
	cout << "\nAfter deleting position 2, size = " << patients.getSize() << endl;

	wards.insertEnd(Ward(1, "Ward A", "General", 10, 4, "Open"));
	equipment.insertEnd(Equipment(7, "Ventilator", "Respiratory", "ICU", "Working", "10/01/2026"));
	wards.getAt(0)->display();
	equipment.getAt(0)->display();

	// searching
	cout << "\nLinear search ID 150 -> position " << linearSearchPatientByID(patients, 150) << endl;
	cout << "Linear search ID 999 -> position " << linearSearchPatientByID(patients, 999) << endl;

	// sorting + binary search
	int n;
	Patient* arr = listToArray(patients, n);
	sortComparisons = 0;
	mergeSort(arr, 0, n - 1, BY_ID);
	cout << "\nMerge sort by ID (" << sortComparisons << " comparisons):" << endl;
	for(int i = 0; i < n; i++){
		arr[i].display();
	}
	cout << "Binary search ID 150 -> index " << binarySearchPatientByID(arr, n, 150) << endl;
	delete[] arr;

	arr = listToArray(patients, n);
	sortComparisons = 0;
	insertionSort(arr, n, BY_PRIORITY);
	cout << "\nInsertion sort by priority (" << sortComparisons << " comparisons):" << endl;
	for(int i = 0; i < n; i++){
		arr[i].display();
	}
	delete[] arr;

	// file I/O round trip
	if(!savePatients(patients, "patients.txt") ||
	   !saveWards(wards, "wards.txt") ||
	   !saveEquipment(equipment, "equipment.txt")){
		cerr << "Could not save test data." << endl;
		return 1;
	}

	LinkedList<Patient> loaded;
	int loadedCount = loadPatients(loaded, "patients.txt");
	cout << "\nLoaded " << loadedCount << " patients from file" << endl;
	Patient* firstLoadedPatient = loaded.getAt(0);
	if(firstLoadedPatient == NULL){
		cerr << "Could not load any patients from file." << endl;
		return 1;
	}
	firstLoadedPatient->display();

	return 0;
}