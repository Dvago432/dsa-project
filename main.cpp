#include <iostream>
#include <string>
#include <limits>
#include "Patient.h"
#include "Ward.h"
#include "Equipment.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include "BST.h"
#include "hashTable.h"
#include "Graph.h"
#include "Searching.h"
#include "Sorting.h"
#include "FileManager.h"

using namespace std;

// Helper to safely clear input buffer after cin >>
void clearInput() {
    cin.clear();
    cin.ignore(10000, '\n');
}

// Sync BST with current patient list
void syncBST(LinkedList<Patient>& list, BST& bst) {
    // Note: BST destructor will clean up previous nodes if re-instantiated,
    // or we can insert all patients
    for (int i = 0; i < list.getSize(); i++) {
        const Patient* p = list.getAt(i);
        if (p != nullptr) {
            bst.insertPatient(*p);
        }
    }
}

// Sync Hash Table with current patient list
void syncPatientHash(LinkedList<Patient>& list, hashTable<Patient>& table) {
    table.clear();
    for (int i = 0; i < list.getSize(); i++) {
        const Patient* p = list.getAt(i);
        if (p != nullptr) {
            table.insert(to_string(p->getPatientID()), *p);
        }
    }
}

// Sync Hash Table with current equipment list
void syncEquipmentHash(LinkedList<Equipment>& list, hashTable<Equipment>& table) {
    table.clear();
    for (int i = 0; i < list.getSize(); i++) {
        const Equipment* e = list.getAt(i);
        if (e != nullptr) {
            table.insert(to_string(e->getEquipmentID()), *e);
        }
    }
}

// Find a ward by name in the wards list
Ward* findWardByName(LinkedList<Ward>& wards, const string& name) {
    for (int i = 0; i < wards.getSize(); i++) {
        Ward* w = wards.getAt(i);
        if (w != nullptr && w->getWardName() == name) {
            return w;
        }
    }
    return nullptr;
}

// -------------------------------------------------------------
// MODULE 1: PATIENT MANAGEMENT
// -------------------------------------------------------------
void handlePatientManagement(LinkedList<Patient>& patients,
                             LinkedList<Ward>& wards,
                             BST& patientBST,
                             hashTable<Patient>& patientHash,
                             Stack& undoStack) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "       1. PATIENT MANAGEMENT MENU       \n";
        cout << "========================================\n";
        cout << " 1. Display All Patients\n";
        cout << " 2. Add New Patient\n";
        cout << " 3. Update Patient Status\n";
        cout << " 4. Discharge Patient (Records to Undo Stack)\n";
        cout << " 5. Delete Patient Record\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            if (patients.isEmpty()) {
                cout << "No patients registered in the system." << endl;
            } else {
                cout << "\n--- Current Patient Records (" << patients.getSize() << ") ---\n";
                for (int i = 0; i < patients.getSize(); i++) {
                    patients.getAt(i)->display();
                }
            }
        } else if (choice == 2) {
            int id, age, day, month, year, priority;
            string name, condition, wardName, status;

            cout << "Enter Patient ID (number): ";
            cin >> id;
            if (linearSearchPatientByID(patients, id) != -1) {
                cout << "Error: Patient with ID " << id << " already exists!" << endl;
                continue;
            }
            clearInput();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            clearInput();
            cout << "Enter Condition: ";
            getline(cin, condition);
            cout << "Enter Assigned Ward: ";
            getline(cin, wardName);
            cout << "Enter Admit Date (day month year, e.g. 15 3 2026): ";
            cin >> day >> month >> year;
            clearInput();
            cout << "Enter Status (e.g. Admitted, Waiting, Discharged): ";
            getline(cin, status);
            cout << "Enter Priority (1-Emergency, 2-Critical, 3-Urgent, 4-Normal): ";
            cin >> priority;

            Patient newPatient(id, name, age, condition, wardName, day, month, year, status, priority);
            patients.insertEnd(newPatient);
            patientBST.insertPatient(newPatient);
            patientHash.insert(to_string(id), newPatient);

            // Update ward occupancy if ward exists
            Ward* w = findWardByName(wards, wardName);
            if (w != nullptr) {
                w->setCurrentOccupancy(w->getCurrentOccupancy() + 1);
            }

            cout << "Patient " << name << " added successfully." << endl;
        } else if (choice == 3) {
            int id;
            cout << "Enter Patient ID to update: ";
            cin >> id;
            int pos = linearSearchPatientByID(patients, id);
            if (pos == -1) {
                cout << "Patient not found." << endl;
                continue;
            }
            Patient* p = patients.getAt(pos);
            clearInput();
            cout << "Current Status: " << p->getStatus() << endl;
            cout << "Enter New Status: ";
            string newStatus;
            getline(cin, newStatus);

            // Push action to undo stack
            undoStack.push(UndoAction("UPDATE_STATUS", to_string(p->getPatientID()), p->getStatus(), p->getAssignedWard()));

            p->setStatus(newStatus);
            patientBST.insertPatient(*p);
            patientHash.insert(to_string(id), *p);
            cout << "Patient status updated successfully." << endl;
        } else if (choice == 4) {
            int id;
            cout << "Enter Patient ID to discharge: ";
            cin >> id;
            int pos = linearSearchPatientByID(patients, id);
            if (pos == -1) {
                cout << "Patient not found." << endl;
                continue;
            }
            Patient* p = patients.getAt(pos);

            // Save undo action
            undoStack.push(UndoAction("DISCHARGE", to_string(p->getPatientID()), p->getStatus(), p->getAssignedWard()));

            // Decrement ward occupancy
            Ward* w = findWardByName(wards, p->getAssignedWard());
            if (w != nullptr && w->getCurrentOccupancy() > 0) {
                w->setCurrentOccupancy(w->getCurrentOccupancy() - 1);
            }

            p->setStatus("Discharged");
            patientBST.insertPatient(*p);
            patientHash.insert(to_string(id), *p);
            cout << "Patient " << p->getName() << " discharged. Undo action recorded." << endl;
        } else if (choice == 5) {
            int id;
            cout << "Enter Patient ID to delete: ";
            cin >> id;
            int pos = linearSearchPatientByID(patients, id);
            if (pos == -1) {
                cout << "Patient not found." << endl;
                continue;
            }
            patients.deleteAt(pos);
            patientBST.deletePatient(id);
            patientHash.remove(to_string(id));
            cout << "Patient ID " << id << " deleted from linked list, BST, and Hash Table." << endl;
        }
    }
}

// -------------------------------------------------------------
// MODULE 2: WARD MANAGEMENT
// -------------------------------------------------------------
void handleWardManagement(LinkedList<Ward>& wards) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "         2. WARD MANAGEMENT MENU        \n";
        cout << "========================================\n";
        cout << " 1. Display All Wards\n";
        cout << " 2. Add New Ward\n";
        cout << " 3. Update Ward Capacity\n";
        cout << " 4. Delete Ward\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            if (wards.isEmpty()) {
                cout << "No wards available." << endl;
            } else {
                cout << "\n--- Hospital Wards (" << wards.getSize() << ") ---\n";
                for (int i = 0; i < wards.getSize(); i++) {
                    wards.getAt(i)->display();
                }
            }
        } else if (choice == 2) {
            int id, capacity;
            string name, type, status;

            cout << "Enter Ward ID: ";
            cin >> id;
            if (linearSearchWardByID(wards, id) != -1) {
                cout << "Error: Ward with ID " << id << " already exists!" << endl;
                continue;
            }
            clearInput();
            cout << "Enter Ward Name (e.g. Ward A, ICU): ";
            getline(cin, name);
            cout << "Enter Type (General, Intensive, Pediatric): ";
            getline(cin, type);
            cout << "Enter Capacity: ";
            cin >> capacity;
            clearInput();
            cout << "Enter Status (Open/Closed): ";
            getline(cin, status);

            wards.insertEnd(Ward(id, name, type, capacity, 0, status));
            cout << "Ward " << name << " added successfully." << endl;
        } else if (choice == 3) {
            int id, newCap;
            cout << "Enter Ward ID to update: ";
            cin >> id;
            int pos = linearSearchWardByID(wards, id);
            if (pos == -1) {
                cout << "Ward not found." << endl;
                continue;
            }
            cout << "Enter New Capacity: ";
            cin >> newCap;
            wards.getAt(pos)->setCapacity(newCap);
            cout << "Ward capacity updated successfully." << endl;
        } else if (choice == 4) {
            int id;
            cout << "Enter Ward ID to delete: ";
            cin >> id;
            int pos = linearSearchWardByID(wards, id);
            if (pos == -1) {
                cout << "Ward not found." << endl;
                continue;
            }
            wards.deleteAt(pos);
            cout << "Ward deleted successfully." << endl;
        }
    }
}

// -------------------------------------------------------------
// MODULE 3: EQUIPMENT MANAGEMENT
// -------------------------------------------------------------
void handleEquipmentManagement(LinkedList<Equipment>& equipment, hashTable<Equipment>& eqHash) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "       3. EQUIPMENT MANAGEMENT MENU     \n";
        cout << "========================================\n";
        cout << " 1. Display All Equipment\n";
        cout << " 2. Add New Equipment\n";
        cout << " 3. Update Equipment Status/Location\n";
        cout << " 4. Delete Equipment\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            if (equipment.isEmpty()) {
                cout << "No equipment recorded." << endl;
            } else {
                cout << "\n--- Hospital Equipment (" << equipment.getSize() << ") ---\n";
                for (int i = 0; i < equipment.getSize(); i++) {
                    equipment.getAt(i)->display();
                }
            }
        } else if (choice == 2) {
            int id;
            string name, type, location, status, lastServiced;

            cout << "Enter Equipment ID: ";
            cin >> id;
            if (linearSearchEquipmentByID(equipment, id) != -1) {
                cout << "Error: Equipment with ID " << id << " already exists!" << endl;
                continue;
            }
            clearInput();
            cout << "Enter Equipment Name: ";
            getline(cin, name);
            cout << "Enter Type: ";
            getline(cin, type);
            cout << "Enter Location (e.g. ICU, Room 204): ";
            getline(cin, location);
            cout << "Enter Status (Working/Under Maintenance): ";
            getline(cin, status);
            cout << "Enter Last Serviced Date (DD/MM/YYYY): ";
            getline(cin, lastServiced);

            Equipment eq(id, name, type, location, status, lastServiced);
            equipment.insertEnd(eq);
            eqHash.insert(to_string(id), eq);
            cout << "Equipment " << name << " added successfully." << endl;
        } else if (choice == 3) {
            int id;
            cout << "Enter Equipment ID to update: ";
            cin >> id;
            int pos = linearSearchEquipmentByID(equipment, id);
            if (pos == -1) {
                cout << "Equipment not found." << endl;
                continue;
            }
            clearInput();
            Equipment* eq = equipment.getAt(pos);
            cout << "Enter New Location: ";
            string loc, st, serv;
            getline(cin, loc);
            cout << "Enter New Status: ";
            getline(cin, st);
            cout << "Enter Service Date: ";
            getline(cin, serv);

            eq->setEquipmentLocation(loc);
            eq->setEquipmentStatus(st);
            eq->setLastServiced(serv);
            eqHash.insert(to_string(id), *eq);
            cout << "Equipment updated successfully." << endl;
        } else if (choice == 4) {
            int id;
            cout << "Enter Equipment ID to delete: ";
            cin >> id;
            int pos = linearSearchEquipmentByID(equipment, id);
            if (pos == -1) {
                cout << "Equipment not found." << endl;
                continue;
            }
            equipment.deleteAt(pos);
            eqHash.remove(to_string(id));
            cout << "Equipment deleted successfully." << endl;
        }
    }
}

// -------------------------------------------------------------
// MODULE 4: ADMISSION QUEUE (FIFO)
// -------------------------------------------------------------
void handleAdmissionQueue(Queue<Request>& admissionQueue,
                          LinkedList<Patient>& patients,
                          LinkedList<Ward>& wards,
                          Stack& undoStack,
                          BST& patientBST,
                          hashTable<Patient>& patientHash) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "        4. ADMISSION QUEUE (FIFO)       \n";
        cout << "========================================\n";
        cout << " 1. View Admission Queue\n";
        cout << " 2. Enqueue Walk-in Patient Request\n";
        cout << " 3. Process Admission Request (Assign to Ward)\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            admissionQueue.display();
        } else if (choice == 2) {
            clearInput();
            string reqID, pID, pName, type, timeStr, desc;
            cout << "Enter Request ID (e.g. REQ101): ";
            getline(cin, reqID);
            cout << "Enter Patient ID (e.g. 201): ";
            getline(cin, pID);
            cout << "Enter Patient Name: ";
            getline(cin, pName);
            cout << "Enter Request Type (e.g. Walk-in Admission): ";
            getline(cin, type);
            cout << "Enter Time (e.g. 10:30): ";
            getline(cin, timeStr);
            cout << "Enter Description / Symptoms: ";
            getline(cin, desc);

            Request req(reqID, pID, pName, type, timeStr, "Pending", 4, desc);
            admissionQueue.enqueue(req);
        } else if (choice == 3) {
            if (admissionQueue.isEmpty()) {
                cout << "The admission queue is empty." << endl;
                continue;
            }

            Request req;
            if (admissionQueue.dequeue(req)) {
                cout << "\nProcessing Admission for Patient: " << req.getName()
                     << " (ID: " << req.getPatientID() << ")" << endl;

                // Find an available ward with capacity
                Ward* availableWard = nullptr;
                for (int i = 0; i < wards.getSize(); i++) {
                    Ward* w = wards.getAt(i);
                    if (w != nullptr && !w->isFull() && w->getStatus() == "Open") {
                        availableWard = w;
                        break;
                    }
                }

                if (availableWard == nullptr) {
                    cout << "Notice: All wards are currently full or closed! Cannot assign bed immediately." << endl;
                } else {
                    availableWard->setCurrentOccupancy(availableWard->getCurrentOccupancy() + 1);
                    cout << "Assigned Patient to: " << availableWard->getWardName()
                         << " (Occupancy now: " << availableWard->getCurrentOccupancy()
                         << "/" << availableWard->getCapacity() << ")" << endl;

                    int pidInt = atoi(req.getPatientID().c_str());
                    int pos = linearSearchPatientByID(patients, pidInt);
                    string prevWard = "None";
                    string prevStatus = "Waiting";

                    if (pos != -1) {
                        Patient* p = patients.getAt(pos);
                        prevWard = p->getAssignedWard();
                        prevStatus = p->getStatus();
                        p->setAssignedWard(availableWard->getWardName());
                        p->setStatus("Admitted");
                        patientBST.insertPatient(*p);
                        patientHash.insert(to_string(pidInt), *p);
                    } else {
                        // Register new patient record into patient list
                        Patient newP(pidInt, req.getName(), 35, req.getDescription(),
                                     availableWard->getWardName(), 20, 10, 2026, "Admitted", 4);
                        patients.insertEnd(newP);
                        patientBST.insertPatient(newP);
                        patientHash.insert(to_string(pidInt), newP);
                    }

                    // Push to undo stack
                    undoStack.push(UndoAction("WARD_ASSIGNMENT", req.getPatientID(), prevStatus, prevWard));
                    cout << "Admission recorded. Undo action saved." << endl;
                }
            }
        }
    }
}

// -------------------------------------------------------------
// MODULE 5: TRIAGE SYSTEM (PRIORITY QUEUE)
// -------------------------------------------------------------
void handleTriageSystem(PriorityQueue& triageQueue,
                        LinkedList<Patient>& patients,
                        Stack& undoStack,
                        BST& patientBST,
                        hashTable<Patient>& patientHash) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "    5. TRIAGE SYSTEM (PRIORITY HEAP)    \n";
        cout << "========================================\n";
        cout << " 1. View Triage Priority Queue\n";
        cout << " 2. Add Patient to Triage (1=Emergency ... 4=Normal)\n";
        cout << " 3. Process Highest-Priority Patient\n";
        cout << " 4. Peek Highest-Priority Patient\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            triageQueue.display();
        } else if (choice == 2) {
            clearInput();
            string reqID, pID, pName, type, timeStr, desc;
            int priority;

            cout << "Enter Request ID (e.g. TRG01): ";
            getline(cin, reqID);
            cout << "Enter Patient ID: ";
            getline(cin, pID);
            cout << "Enter Patient Name: ";
            getline(cin, pName);
            cout << "Enter Condition/Description: ";
            getline(cin, desc);
            cout << "Enter Priority Level (1-Emergency, 2-Critical, 3-Urgent, 4-Normal): ";
            cin >> priority;
            clearInput();

            Request req(reqID, pID, pName, "Triage Request", "Now", "Pending", priority, desc);
            triageQueue.insert(req);
        } else if (choice == 3) {
            Request req;
            if (triageQueue.removeHighestPriority(req)) {
                cout << "\n>>> EMERGENCY ACTION: Treating Highest Priority Request <<<\n";
                req.displayRequest();

                int pid = atoi(req.getPatientID().c_str());
                int pos = linearSearchPatientByID(patients, pid);
                string prevStatus = "Waiting";
                string prevWard = "Emergency";

                if (pos != -1) {
                    Patient* p = patients.getAt(pos);
                    prevStatus = p->getStatus();
                    prevWard = p->getAssignedWard();
                    p->setStatus("Under Urgent Care");
                    p->setPriority(req.getPriority());
                    patientBST.insertPatient(*p);
                    patientHash.insert(to_string(pid), *p);
                }

                undoStack.push(UndoAction("UPDATE_STATUS", req.getPatientID(), prevStatus, prevWard));
                cout << "Patient " << req.getName() << " prioritized for medical attention." << endl;
            }
        } else if (choice == 4) {
            Request req;
            if (triageQueue.peek(req)) {
                cout << "\n--- Next Highest Priority Patient ---\n";
                req.displayRequest();
            } else {
                cout << "Triage Priority Queue is empty." << endl;
            }
        }
    }
}

// -------------------------------------------------------------
// MODULE 6: UNDO OPERATIONS (STACK)
// -------------------------------------------------------------
void handleUndoOperations(Stack& undoStack,
                          LinkedList<Patient>& patients,
                          LinkedList<Ward>& wards,
                          BST& patientBST,
                          hashTable<Patient>& patientHash) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "       6. UNDO OPERATIONS (STACK)       \n";
        cout << "========================================\n";
        cout << " 1. View Undo Stack History\n";
        cout << " 2. Undo Last Operation\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            undoStack.display();
        } else if (choice == 2) {
            if (undoStack.isEmpty()) {
                cout << "No actions to undo. The stack is empty." << endl;
                continue;
            }

            UndoAction action;
            if (undoStack.pop(action)) {
                cout << "\nReverting Action: " << action.actionType
                     << " for Patient ID: " << action.patientID << endl;

                int pid = atoi(action.patientID.c_str());
                int pos = linearSearchPatientByID(patients, pid);

                if (action.actionType == "DISCHARGE") {
                    if (pos != -1) {
                        Patient* p = patients.getAt(pos);
                        p->setStatus(action.previousStatus);
                        p->setAssignedWard(action.previousWard);

                        // Re-increment ward occupancy
                        Ward* w = findWardByName(wards, action.previousWard);
                        if (w != nullptr) {
                            w->setCurrentOccupancy(w->getCurrentOccupancy() + 1);
                        }

                        patientBST.insertPatient(*p);
                        patientHash.insert(to_string(pid), *p);
                        cout << "Undo Complete: Patient " << pid << " restored to "
                             << action.previousStatus << " in " << action.previousWard << "." << endl;
                    } else {
                        cout << "Warning: Patient record no longer exists to revert." << endl;
                    }
                } else if (action.actionType == "UPDATE_STATUS") {
                    if (pos != -1) {
                        Patient* p = patients.getAt(pos);
                        p->setStatus(action.previousStatus);
                        patientBST.insertPatient(*p);
                        patientHash.insert(to_string(pid), *p);
                        cout << "Undo Complete: Patient " << pid << " status restored to "
                             << action.previousStatus << "." << endl;
                    }
                } else if (action.actionType == "WARD_ASSIGNMENT") {
                    if (pos != -1) {
                        Patient* p = patients.getAt(pos);
                        // Decrement current ward occupancy
                        Ward* currWard = findWardByName(wards, p->getAssignedWard());
                        if (currWard != nullptr && currWard->getCurrentOccupancy() > 0) {
                            currWard->setCurrentOccupancy(currWard->getCurrentOccupancy() - 1);
                        }
                        p->setAssignedWard(action.previousWard);
                        p->setStatus(action.previousStatus);
                        patientBST.insertPatient(*p);
                        patientHash.insert(to_string(pid), *p);
                        cout << "Undo Complete: Ward assignment reverted." << endl;
                    }
                } else {
                    cout << "Action undone successfully." << endl;
                }
            }
        }
    }
}

// -------------------------------------------------------------
// MODULE 7: SEARCHING AND SORTING
// -------------------------------------------------------------
void handleSearchAndSort(LinkedList<Patient>& patients,
                         LinkedList<Ward>& wards,
                         LinkedList<Equipment>& equipment) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "        7. SEARCH & SORT MENU           \n";
        cout << "========================================\n";
        cout << " 1. Linear Search Patient by ID\n";
        cout << " 2. Linear Search Patient by Name\n";
        cout << " 3. Linear Search Ward by ID\n";
        cout << " 4. Linear Search Equipment by ID\n";
        cout << " 5. Binary Search Patient by ID (O(log n))\n";
        cout << " 6. Insertion Sort Patients\n";
        cout << " 7. Merge Sort Patients (O(n log n))\n";
        cout << " 8. Compare Insertion Sort vs Merge Sort\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            int pos = linearSearchPatientByID(patients, id);
            if (pos != -1) {
                cout << "Patient found at list position " << pos << ":\n";
                patients.getAt(pos)->display();
            } else {
                cout << "Patient with ID " << id << " not found." << endl;
            }
        } else if (choice == 2) {
            clearInput();
            string name;
            cout << "Enter Patient Name: ";
            getline(cin, name);
            int pos = linearSearchPatientByName(patients, name);
            if (pos != -1) {
                cout << "Patient found at list position " << pos << ":\n";
                patients.getAt(pos)->display();
            } else {
                cout << "Patient '" << name << "' not found." << endl;
            }
        } else if (choice == 3) {
            int id;
            cout << "Enter Ward ID: ";
            cin >> id;
            int pos = linearSearchWardByID(wards, id);
            if (pos != -1) {
                cout << "Ward found at list position " << pos << ":\n";
                wards.getAt(pos)->display();
            } else {
                cout << "Ward with ID " << id << " not found." << endl;
            }
        } else if (choice == 4) {
            int id;
            cout << "Enter Equipment ID: ";
            cin >> id;
            int pos = linearSearchEquipmentByID(equipment, id);
            if (pos != -1) {
                cout << "Equipment found at list position " << pos << ":\n";
                equipment.getAt(pos)->display();
            } else {
                cout << "Equipment with ID " << id << " not found." << endl;
            }
        } else if (choice == 5) {
            if (patients.isEmpty()) {
                cout << "Patient list is empty." << endl;
                continue;
            }
            int id;
            cout << "Enter Patient ID to Binary Search: ";
            cin >> id;

            // Convert to array and sort by ID first (Binary Search requirement)
            int n;
            Patient* arr = listToArray(patients, n);
            mergeSort(arr, 0, n - 1, BY_ID);

            int idx = binarySearchPatientByID(arr, n, id);
            if (idx != -1) {
                cout << "Patient found via Binary Search at sorted index " << idx << ":\n";
                arr[idx].display();
            } else {
                cout << "Patient ID " << id << " not found in sorted array." << endl;
            }
            delete[] arr;
        } else if (choice == 6 || choice == 7) {
            if (patients.isEmpty()) {
                cout << "Patient list is empty." << endl;
                continue;
            }
            cout << "\nChoose sorting criteria:\n";
            cout << " 1. By Patient ID\n";
            cout << " 2. By Name\n";
            cout << " 3. By Admit Date\n";
            cout << " 4. By Condition Priority (1-Emergency first)\n";
            cout << "Enter criteria (1-4): ";
            int crit;
            cin >> crit;
            if (crit < 1 || crit > 4) crit = BY_ID;

            int n;
            Patient* arr = listToArray(patients, n);
            sortComparisons = 0;

            if (choice == 6) {
                insertionSort(arr, n, crit);
                cout << "\n--- Patients sorted with Insertion Sort ("
                     << sortComparisons << " comparisons) ---\n";
            } else {
                mergeSort(arr, 0, n - 1, crit);
                cout << "\n--- Patients sorted with Merge Sort ("
                     << sortComparisons << " comparisons) ---\n";
            }

            for (int i = 0; i < n; i++) {
                arr[i].display();
            }
            delete[] arr;
        } else if (choice == 8) {
            if (patients.isEmpty()) {
                cout << "Patient list is empty." << endl;
                continue;
            }
            int n1, n2;
            Patient* arr1 = listToArray(patients, n1);
            Patient* arr2 = listToArray(patients, n2);

            sortComparisons = 0;
            insertionSort(arr1, n1, BY_ID);
            long insertionComps = sortComparisons;

            sortComparisons = 0;
            mergeSort(arr2, 0, n2 - 1, BY_ID);
            long mergeComps = sortComparisons;

            cout << "\n============================================\n";
            cout << "      ALGORITHM COMPARISON (N = " << n1 << ")      \n";
            cout << "============================================\n";
            cout << " Insertion Sort: " << insertionComps << " comparisons | Complexity: O(n^2)\n";
            cout << " Merge Sort    : " << mergeComps     << " comparisons | Complexity: O(n log n)\n";
            cout << "============================================\n";

            delete[] arr1;
            delete[] arr2;
        }
    }
}

// -------------------------------------------------------------
// MODULE 8: PATIENT BINARY SEARCH TREE (BST)
// -------------------------------------------------------------
void handlePatientBST(BST& patientBST, LinkedList<Patient>& patients) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "          8. PATIENT BST MENU           \n";
        cout << "========================================\n";
        cout << " 1. Inorder Traversal (Sorted by Patient ID)\n";
        cout << " 2. Preorder Traversal\n";
        cout << " 3. Level-Order Traversal\n";
        cout << " 4. Search Patient in BST by ID\n";
        cout << " 5. Delete Patient from BST\n";
        cout << " 6. Rebuild BST from Current Patient List\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            patientBST.inorder_traverse();
        } else if (choice == 2) {
            patientBST.preorder_traverse();
        } else if (choice == 3) {
            patientBST.levelOrder_traverse();
        } else if (choice == 4) {
            int id;
            cout << "Enter Patient ID: ";
            cin >> id;
            Patient* p = patientBST.getPatient(id);
            if (p != nullptr) {
                cout << "Patient found in BST:\n";
                p->display();
            } else {
                cout << "Patient ID " << id << " not found in BST." << endl;
            }
        } else if (choice == 5) {
            int id;
            cout << "Enter Patient ID to delete from BST: ";
            cin >> id;
            patientBST.deletePatient(id);
        } else if (choice == 6) {
            syncBST(patients, patientBST);
            cout << "BST rebuilt from " << patients.getSize() << " patients in linked list." << endl;
        }
    }
}

// -------------------------------------------------------------
// MODULE 9: RESOURCE LOOKUP (HASH TABLE)
// -------------------------------------------------------------
void handleResourceLookup(hashTable<Patient>& patientHash,
                         hashTable<Equipment>& eqHash) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "      9. RESOURCE LOOKUP (HASH TABLE)   \n";
        cout << "========================================\n";
        cout << " 1. Instant Lookup Patient by ID (O(1))\n";
        cout << " 2. Instant Lookup Equipment by ID (O(1))\n";
        cout << " 3. Display All Patients in Hash Table\n";
        cout << " 4. Display All Equipment in Hash Table\n";
        cout << " 5. Remove Patient from Hash Table\n";
        cout << " 6. Remove Equipment from Hash Table\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            clearInput();
            string key;
            cout << "Enter Patient ID: ";
            getline(cin, key);
            Patient* p = patientHash.get(key);
            if (p != nullptr) {
                cout << "Found Patient in Hash Table (O(1) lookup):\n";
                p->display();
            } else {
                cout << "Patient ID '" << key << "' not found in Hash Table." << endl;
            }
        } else if (choice == 2) {
            clearInput();
            string key;
            cout << "Enter Equipment ID: ";
            getline(cin, key);
            Equipment* e = eqHash.get(key);
            if (e != nullptr) {
                cout << "Found Equipment in Hash Table (O(1) lookup):\n";
                e->display();
            } else {
                cout << "Equipment ID '" << key << "' not found in Hash Table." << endl;
            }
        } else if (choice == 3) {
            patientHash.displayAll();
        } else if (choice == 4) {
            eqHash.displayAll();
        } else if (choice == 5) {
            clearInput();
            string key;
            cout << "Enter Patient ID to remove: ";
            getline(cin, key);
            if (patientHash.remove(key)) {
                cout << "Patient " << key << " removed from Hash Table." << endl;
            } else {
                cout << "Key not found in Hash Table." << endl;
            }
        } else if (choice == 6) {
            clearInput();
            string key;
            cout << "Enter Equipment ID to remove: ";
            getline(cin, key);
            if (eqHash.remove(key)) {
                cout << "Equipment " << key << " removed from Hash Table." << endl;
            } else {
                cout << "Key not found in Hash Table." << endl;
            }
        }
    }
}

// -------------------------------------------------------------
// MODULE 10: HOSPITAL NAVIGATION (GRAPH)
// -------------------------------------------------------------
void handleHospitalNavigation(Graph& hospitalMap) {
    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "     10. HOSPITAL NAVIGATION (GRAPH)    \n";
        cout << "========================================\n";
        cout << " 1. Display Campus Map & Corridors\n";
        cout << " 2. Breadth-First Search (BFS) Reachability\n";
        cout << " 3. Depth-First Search (DFS) Traversal\n";
        cout << " 4. Find Shortest Route (Dijkstra's Algorithm)\n";
        cout << " 0. Return to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        if (choice == 1) {
            hospitalMap.displayMap();
        } else if (choice == 2) {
            clearInput();
            string start;
            cout << "Enter Starting Department (e.g. Reception, Emergency, ICU): ";
            getline(cin, start);
            hospitalMap.BFS(start);
        } else if (choice == 3) {
            clearInput();
            string start;
            cout << "Enter Starting Department: ";
            getline(cin, start);
            hospitalMap.DFS(start);
        } else if (choice == 4) {
            clearInput();
            string start, dest;
            cout << "Enter Starting Department (e.g. Reception): ";
            getline(cin, start);
            cout << "Enter Destination Department (e.g. Radiology): ";
            getline(cin, dest);
            hospitalMap.dijkstra(start, dest);
        }
    }
}

// -------------------------------------------------------------
// MODULE 11: SYSTEM ANALYSIS & COMPLEXITY
// -------------------------------------------------------------
void handleSystemAnalysis() {
    cout << "\n========================================================================\n";
    cout << "             11. SYSTEM ANALYSIS & ALGORITHM COMPLEXITY                 \n";
    cout << "========================================================================\n";
    cout << " Operation                | Data Structure | Best     | Average  | Worst   \n";
    cout << "--------------------------+----------------+----------+----------+---------\n";
    cout << " Enqueue patient          | Queue          | O(1)     | O(1)     | O(1)    \n";
    cout << " Dequeue patient          | Queue          | O(1)     | O(1)     | O(1)    \n";
    cout << " Push undo                | Stack          | O(1)     | O(1)     | O(1)    \n";
    cout << " Triage insert            | Min-Heap       | O(1)     | O(log n) | O(log n)\n";
    cout << " Triage extract-highest   | Min-Heap       | O(log n) | O(log n) | O(log n)\n";
    cout << " Linear search            | Linked List    | O(1)     | O(n)     | O(n)    \n";
    cout << " Binary search            | Sorted Array   | O(1)     | O(log n) | O(log n)\n";
    cout << " Insertion sort           | Array          | O(n)     | O(n^2)   | O(n^2)  \n";
    cout << " Merge sort               | Array          | O(nlogn) | O(nlogn) | O(nlogn)\n";
    cout << " BST insert / search      | BST            | O(1)     | O(log n) | O(n)    \n";
    cout << " Hash table lookup        | Hash Table     | O(1)     | O(1)     | O(n)    \n";
    cout << " BFS traversal            | Graph (Queue)  | O(V+E)   | O(V+E)   | O(V+E)  \n";
    cout << " DFS traversal            | Graph (Stack)  | O(V+E)   | O(V+E)   | O(V+E)  \n";
    cout << " Dijkstra's shortest path | Graph (Matrix) | O(V^2)   | O(V^2)   | O(V^2)  \n";
    cout << "========================================================================\n";
    cout << "Design Justification Highlights:\n";
    cout << " * Custom Linked List allows O(1) dynamic insertions without reallocations.\n";
    cout << " * Min-Heap guarantees immediate access to highest-priority emergency patients.\n";
    cout << " * Hash Table provides instant O(1) resource lookup using string IDs.\n";
    cout << " * BST maintains patients in sorted order by ID and allows efficient searches.\n";
    cout << " * Graph with Dijkstra finds optimal transfer routes between departments.\n";
    cout << "========================================================================\n";
}

// -------------------------------------------------------------
// MAIN FUNCTION & SYSTEM LOOP
// -------------------------------------------------------------
int main() {
    LinkedList<Patient> patients;
    LinkedList<Ward> wards;
    LinkedList<Equipment> equipment;

    Queue<Request> admissionQueue;
    PriorityQueue triageQueue;
    Stack undoStack;

    BST patientBST;
    hashTable<Patient> patientHash(101);
    hashTable<Equipment> equipmentHash(101);

    Graph hospitalMap;
    hospitalMap.loadDefaultHospitalMap();

    // Load initial data from files
    cout << "Loading hospital database files..." << endl;
    int pLoaded = loadPatients(patients, "patients.txt");
    int wLoaded = loadWards(wards, "wards.txt");
    int eLoaded = loadEquipment(equipment, "equipment.txt");

    // Populate default wards if wards file is empty
    if (wLoaded == 0) {
        wards.insertEnd(Ward(1, "Ward A", "General", 10, 2, "Open"));
        wards.insertEnd(Ward(2, "Ward B", "Intensive Care", 5, 1, "Open"));
        wards.insertEnd(Ward(3, "Ward C", "Pediatric", 8, 1, "Open"));
        saveWards(wards, "wards.txt");
    }

    // Populate BST and Hash Tables
    syncBST(patients, patientBST);
    syncPatientHash(patients, patientHash);
    syncEquipmentHash(equipment, equipmentHash);

    cout << "Startup summary: Loaded " << pLoaded << " patients, "
         << wards.getSize() << " wards, " << eLoaded << " equipment." << endl;

    int choice = -1;
    while (choice != 0) {
        cout << "\n========================================\n";
        cout << "   CS3400 HOSPITAL MANAGEMENT SYSTEM    \n";
        cout << "========================================\n";
        cout << " 1. Patient Management\n";
        cout << " 2. Ward Management\n";
        cout << " 3. Equipment Management\n";
        cout << " 4. Admission Queue\n";
        cout << " 5. Triage System (Priority Queue)\n";
        cout << " 6. Undo Last Operation\n";
        cout << " 7. Search & Sort\n";
        cout << " 8. Patient BST\n";
        cout << " 9. Resource Lookup (Hash Table)\n";
        cout << "10. Hospital Navigation (Graph)\n";
        cout << "11. System Analysis & Complexity\n";
        cout << " 0. Exit\n";
        cout << "========================================\n";
        cout << "Select option: ";

        if (!(cin >> choice)) {
            clearInput();
            continue;
        }

        switch (choice) {
            case 1:
                handlePatientManagement(patients, wards, patientBST, patientHash, undoStack);
                break;
            case 2:
                handleWardManagement(wards);
                break;
            case 3:
                handleEquipmentManagement(equipment, equipmentHash);
                break;
            case 4:
                handleAdmissionQueue(admissionQueue, patients, wards, undoStack, patientBST, patientHash);
                break;
            case 5:
                handleTriageSystem(triageQueue, patients, undoStack, patientBST, patientHash);
                break;
            case 6:
                handleUndoOperations(undoStack, patients, wards, patientBST, patientHash);
                break;
            case 7:
                handleSearchAndSort(patients, wards, equipment);
                break;
            case 8:
                handlePatientBST(patientBST, patients);
                break;
            case 9:
                handleResourceLookup(patientHash, equipmentHash);
                break;
            case 10:
                handleHospitalNavigation(hospitalMap);
                break;
            case 11:
                handleSystemAnalysis();
                break;
            case 0:
                cout << "\nSaving system records..." << endl;
                savePatients(patients, "patients.txt");
                saveWards(wards, "wards.txt");
                saveEquipment(equipment, "equipment.txt");
                cout << "Records saved successfully. Exiting Hospital Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please choose from 0 to 11." << endl;
                break;
        }
    }

    return 0;
}
