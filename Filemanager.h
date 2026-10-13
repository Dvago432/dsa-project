#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include "LinkedList.h"
#include "Patient.h"
#include "Ward.h"
#include "Equipment.h"
using namespace std;

// load functions return how many records were read (0 if the file is missing)
int loadPatients(LinkedList<Patient>& list, string filename);
int loadWards(LinkedList<Ward>& list, string filename);
int loadEquipment(LinkedList<Equipment>& list, string filename);

// save functions return true if the file was written
bool savePatients(LinkedList<Patient>& list, string filename);
bool saveWards(LinkedList<Ward>& list, string filename);
bool saveEquipment(LinkedList<Equipment>& list, string filename);

#endif