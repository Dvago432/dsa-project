#include <iostream>
#include "Ward.h"
using namespace std;

Ward::Ward(){
	wardID = 0;
	wardName = "";
	type = "";
	capacity = 0;
	currentOccupancy = 0;
	status = "";
}

Ward::Ward(int wi, string nm, string ty, int cap, int co, string sta){
	wardID = wi;
	wardName = nm;
	type = ty;
	capacity = cap;
	currentOccupancy = co;
	status = sta;
}

void Ward::setWardID(int wi){ wardID = wi; }
int Ward::getWardID() const{ return wardID; }

void Ward::setWardName(string nm){ wardName = nm; }
string Ward::getWardName() const{ return wardName; }

void Ward::setType(string ty){ type = ty; }
string Ward::getType() const{ return type; }

void Ward::setCapacity(int cap){ capacity = cap; }
int Ward::getCapacity() const{ return capacity; }

void Ward::setCurrentOccupancy(int co){ currentOccupancy = co; }
int Ward::getCurrentOccupancy() const{ return currentOccupancy; }

void Ward::setStatus(string sta){ status = sta; }
string Ward::getStatus() const{ return status; }

bool Ward::isFull() const{
	return currentOccupancy >= capacity;
}

void Ward::display() const{
	cout << "ID: " << wardID << " | " << wardName << " | " << type
	     << " | Occupancy: " << currentOccupancy << "/" << capacity
	     << " | " << status << endl;
}