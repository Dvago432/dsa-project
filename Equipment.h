#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <string>
using namespace std;

class Equipment{

	private:

		int equipmentID;
		string equipmentName;
		string equipmentType;
		string equipmentLocation;
		string equipmentStatus;
		string lastServiced;

	public:

		Equipment();
		Equipment(int eid, string en, string ety, string loc, string esta, string ls);

		void setEquipmentID(int eid);
		int getEquipmentID() const;

		void setEquipmentName(string en);
		string getEquipmentName() const;

		void setEquipmentType(string ety);
		string getEquipmentType() const;

		void setEquipmentLocation(string loc);
		string getEquipmentLocation() const;

		void setEquipmentStatus(string esta);
		string getEquipmentStatus() const;

		void setLastServiced(string ls);
		string getLastServiced() const;

		void display() const;
};

#endif
