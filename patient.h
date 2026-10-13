#ifndef PATIENT_H
#define PATIENT_H
#include <string>
using namespace std;

struct Date{

	int day;
	int month;
	int year;
};

class Patient{

	private:

		int patientID;
		string name;
		int age;
		string condition;
		string assignedWard;
		Date date;
		string status;
		int priority; //1 Emergency, 2 Critical, 3 Urgent, 4 Normal

	public:

		Patient();
		Patient(int pi, string na, int ag, string con, string aw, int da, int mo, int yr, string st, int pr);

		void setPatientID(int pi);
		int getPatientID() const;

		void setName(string na);
		string getName() const;

		void setAge(int ag);
		int getAge() const;

		void setCondition(string con);
		string getCondition() const;

		void setAssignedWard(string aw);
		string getAssignedWard() const;

		void setDate(int da, int mo, int yr);
		Date getDate() const;

		void setStatus(string st);
		string getStatus() const;

		void setPriority(int pr);
		int getPriority() const;

		void display() const;
};

#endif
