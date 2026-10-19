#include <iostream>
#include "Equipment.h"
using namespace std;

Equipment::Equipment(){
	equipmentID = 0;
	equipmentName = "";
	equipmentType = "";
	equipmentLocation = "";
	equipmentStatus = "";
	lastServiced = "";
}

Equipment::Equipment(int eid, string en, string ety, string loc, string esta, string ls){
	equipmentID = eid;
	equipmentName = en;
	equipmentType = ety;
	equipmentLocation = loc;
	equipmentStatus = esta;
	lastServiced = ls;
}

void Equipment::setEquipmentID(int eid){ equipmentID = eid; }
int Equipment::getEquipmentID() const{ return equipmentID; }

void Equipment::setEquipmentName(string en){ equipmentName = en; }
string Equipment::getEquipmentName() const{ return equipmentName; }

void Equipment::setEquipmentType(string ety){
     equipmentType = ety; }
string Equipment::getEquipmentType() const{ 
    return equipmentType; }

void Equipment::setEquipmentLocation(string loc){ 
    equipmentLocation = loc; }
string Equipment::getEquipmentLocation() const
{
    return equipmentLocation;
}

void Equipment::setEquipmentStatus(string esta){
     equipmentStatus = esta; }
string Equipment::getEquipmentStatus() const{ 
    return equipmentStatus; }

void Equipment::setLastServiced(string ls){ lastServiced = ls; }
string Equipment::getLastServiced() const{ return lastServiced; }

void Equipment::display() const{
	cout << "ID: " << equipmentID << " | " << equipmentName << " | " << equipmentType
	     << " | Location: " << equipmentLocation << " | " << equipmentStatus
	     << " | Last serviced: " << lastServiced << endl;
}