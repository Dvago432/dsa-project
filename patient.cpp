#include <iostream>
#include "Patient.h"
using namespace std;

Patient::Patient(){
	patientID = 0;
	name = "";
	age = 0;
	condition = "";
	assignedWard = "";
	date.day = 0;
	date.month = 0;
	date.year = 0;
	status = "";
	priority = 4;
}

Patient::Patient(int pi, string na, int ag, string con, string aw, int da, int mo, int yr, string st, int pr){
	patientID = pi;
	name = na;
	age = ag;
	condition = con;
	assignedWard = aw;
	date.day = da;
	date.month = mo;
	date.year = yr;
	status = st;
	priority = pr;
}

void Patient::setPatientID(int pi){ patientID = pi; }
int Patient::getPatientID() const{ return patientID; }

void Patient::setName(string na){ name = na; }
string Patient::getName() const{ return name; }

void Patient::setAge(int ag){ age = ag; }
int Patient::getAge() const{ return age; }

void Patient::setCondition(string con){ condition = con; }
string Patient::getCondition() const{ return condition; }

void Patient::setAssignedWard(string aw){ assignedWard = aw; }
string Patient::getAssignedWard() const{ return assignedWard; }

void Patient::setDate(int da, int mo, int yr){
	date.day = da;
	date.month = mo;
	date.year = yr;
}
Date Patient::getDate() const{ return date; }

void Patient::setStatus(string st){ status = st; }
string Patient::getStatus() const{ return status; }

void Patient::setPriority(int pr){ priority = pr; }
int Patient::getPriority() const{ return priority; }

void Patient::display() const{
	cout << "ID: " << patientID << " | " << name << " | Age: " << age
	     << " | " << condition << " | Ward: " << assignedWard
	     << " | Admitted: " << date.day << "/" << date.month << "/" << date.year
	     << " | " << status << " | Priority: " << priority << endl;
}
