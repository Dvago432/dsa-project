#ifndef WARD_H
#define WARD_H
#include <string>
using namespace std;

class Ward{

	private:

		int wardID;
		string wardName;
		string type;
		int capacity; //maximum number of patients
		int currentOccupancy; //current number of patients
		string status; // operational condition, capacity, or availability to receive patients

	public:

		Ward();
		Ward(int wi, string nm, string ty, int cap, int co, string sta);

		void setWardID(int wi);
		int getWardID() const;

		void setWardName(string nm);
		string getWardName() const;

		void setType(string ty);
		string getType() const;

		void setCapacity(int cap);
		int getCapacity() const;

		void setCurrentOccupancy(int co);
		int getCurrentOccupancy() const;

		void setStatus(string sta);
		string getStatus() const;

		bool isFull() const;
		void display() const;
};

#endif
