#ifndef REQUEST_H
#define REQUEST_H
#include <string>
# include <iostream>
using namespace std;

class Request{
	private:
		string patientName;
		string requestID;
		string patientID;
		string type;
		string time;
		string status;
		string description;
		int Priority; 
	
	public:
		
		Request();
		Request(string RID,string PID,string type,string time,string st,string ds,int pr,string);
		void setName(string);
		void setRequestID(string);
		void setPatientID(string);
		void setType(string);
		void setStatus(string);
		void setDescription(string);
		void setPriority(int);
		string getName() const;
		string getPatientID() const;
		string getRequestID() const;
		string getType();
		string getTime();
		string getStatus();
		int getPriority() const;
		string getDescription();
		void displayRequest() const;
};

#endif


