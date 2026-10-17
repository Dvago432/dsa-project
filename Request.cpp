#include "Request.h"
#include <iostream>

Request::Request(){
	patientName=" ";
	requestID=" ";
	patientID=" ";
	type=" ";
	time=" ";
	status="Pending";
	Priority=4;
	description=" ";
}

Request::Request(string RID,string PID,string nm,string type,string time,string st,int pr,string ds){
	
	requestID=RID;
	patientName=nm;
	patientID=PID;
	this->type=type;
	status=st;
	this->time=time;
	Priority=pr;
	description=ds;
}

string Request::getRequestID() const{
	return requestID;
}

string Request::getStatus(){
	return status;
}

string Request::getPatientID() const{
	return patientID;
}

string Request::getTime(){
	return time;
}

int Request::getPriority() const{
	return Priority;
}

string Request::getDescription(){
	return description;
}
 
void Request::setRequestID(string RID){
	requestID=RID;
}

void Request::setPatientID(string PID){
	patientID=PID;
}
void Request::setType(string ty){
	type=ty;
}

void Request:: setStatus(string st){
	status=st;
}
void Request::setDescription(string ds){
	description=ds;
}
void Request::setPriority(int ps){
	
	if (ps>=1 && ps<=4){
		this->Priority=ps;
	}
	
}

void Request::setName(string nm){
	patientName=nm;
}

string Request::getName() const{
	return patientName;
}

void Request::displayRequest() const{
    cout << "\n----- Request Information -----" << endl;
    cout << "Request ID: " << requestID << endl;
    cout << "Patient ID: " << patientID << endl;
    cout << "Patient Name: " << patientName << endl;
    cout << "Request Type: " << type << endl;
    cout << "Time: " << time << endl;
    cout << "Status: " << status << endl;
    cout << "Priority: " << Priority << endl;
    cout << "Description: " << description << endl;
    cout << "-------------------------------" << endl;
}