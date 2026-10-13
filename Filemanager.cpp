#include <fstream>
#include <sstream>
#include <cstdlib>
#include "FileManager.h"

// Each record is one line, fields separated by |
// patients : id|name|age|condition|ward|day|month|year|status|priority
// wards    : id|name|type|capacity|occupancy|status
// equipment: id|name|type|location|status|lastServiced

int loadPatients(LinkedList<Patient>& list, string filename){
	ifstream file(filename.c_str());
	if(!file){
		return 0;
	}

	string line;
	int count = 0;
	while(getline(file, line)){
		if(line == ""){
			continue;
		}
		stringstream ss(line);
		string f[10];
		for(int i = 0; i < 10; i++){
			getline(ss, f[i], '|');
		}
		Patient p(atoi(f[0].c_str()), f[1], atoi(f[2].c_str()), f[3], f[4],
		          atoi(f[5].c_str()), atoi(f[6].c_str()), atoi(f[7].c_str()),
		          f[8], atoi(f[9].c_str()));
		list.insertEnd(p);
		count++;
	}
	file.close();
	return count;
}

int loadWards(LinkedList<Ward>& list, string filename){
	ifstream file(filename.c_str());
	if(!file){
		return 0;
	}

	string line;
	int count = 0;
	while(getline(file, line)){
		if(line == ""){
			continue;
		}
		stringstream ss(line);
		string f[6];
		for(int i = 0; i < 6; i++){
			getline(ss, f[i], '|');
		}
		Ward w(atoi(f[0].c_str()), f[1], f[2], atoi(f[3].c_str()), atoi(f[4].c_str()), f[5]);
		list.insertEnd(w);
		count++;
	}
	file.close();
	return count;
}

int loadEquipment(LinkedList<Equipment>& list, string filename){
	ifstream file(filename.c_str());
	if(!file){
		return 0;
	}

	string line;
	int count = 0;
	while(getline(file, line)){
		if(line == ""){
			continue;
		}
		stringstream ss(line);
		string f[6];
		for(int i = 0; i < 6; i++){
			getline(ss, f[i], '|');
		}
		Equipment e(atoi(f[0].c_str()), f[1], f[2], f[3], f[4], f[5]);
		list.insertEnd(e);
		count++;
	}
	file.close();
	return count;
}

bool savePatients(LinkedList<Patient>& list, string filename){
	ofstream file(filename.c_str());
	if(!file){
		return false;
	}

	Node<Patient>* temp = list.getHead();
	while(temp != NULL){
		Date d = temp->data.getDate();
		file << temp->data.getPatientID() << "|" << temp->data.getName() << "|"
		     << temp->data.getAge() << "|" << temp->data.getCondition() << "|"
		     << temp->data.getAssignedWard() << "|" << d.day << "|" << d.month << "|"
		     << d.year << "|" << temp->data.getStatus() << "|"
		     << temp->data.getPriority() << endl;
		temp = temp->next;
	}
	file.close();
	return true;
}

bool saveWards(LinkedList<Ward>& list, string filename){
	ofstream file(filename.c_str());
	if(!file){
		return false;
	}

	Node<Ward>* temp = list.getHead();
	while(temp != NULL){
		file << temp->data.getWardID() << "|" << temp->data.getWardName() << "|"
		     << temp->data.getType() << "|" << temp->data.getCapacity() << "|"
		     << temp->data.getCurrentOccupancy() << "|" << temp->data.getStatus() << endl;
		temp = temp->next;
	}
	file.close();
	return true;
}

bool saveEquipment(LinkedList<Equipment>& list, string filename){
	ofstream file(filename.c_str());
	if(!file){
		return false;
	}

	Node<Equipment>* temp = list.getHead();
	while(temp != NULL){
		file << temp->data.getEquipmentID() << "|" << temp->data.getEquipmentName() << "|"
		     << temp->data.getEquipmentType() << "|" << temp->data.getEquipmentLocation() << "|"
		     << temp->data.getEquipmentStatus() << "|" << temp->data.getLastServiced() << endl;
		temp = temp->next;
	}
	file.close();
	return true;
}