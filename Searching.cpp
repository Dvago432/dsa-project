#include "Searching.h"

int linearSearchPatientByID(LinkedList<Patient>& list, int id){
	Node<Patient>* temp = list.getHead();
	int pos = 0;
	while(temp != NULL){
		if(temp->data.getPatientID() == id){
			return pos;
		}
		temp = temp->next;
		pos++;
	}
	return -1;
}

int linearSearchPatientByName(LinkedList<Patient>& list, string name){
	Node<Patient>* temp = list.getHead();
	int pos = 0;
	while(temp != NULL){
		if(temp->data.getName() == name){
			return pos;
		}
		temp = temp->next;
		pos++;
	}
	return -1;
}

int linearSearchWardByID(LinkedList<Ward>& list, int id){
	Node<Ward>* temp = list.getHead();
	int pos = 0;
	while(temp != NULL){
		if(temp->data.getWardID() == id){
			return pos;
		}
		temp = temp->next;
		pos++;
	}
	return -1;
}

int linearSearchEquipmentByID(LinkedList<Equipment>& list, int id){
	Node<Equipment>* temp = list.getHead();
	int pos = 0;
	while(temp != NULL){
		if(temp->data.getEquipmentID() == id){
			return pos;
		}
		temp = temp->next;
		pos++;
	}
	return -1;
}

int binarySearchPatientByID(Patient arr[], int n, int id){
	int low = 0;
	int high = n - 1;

	while(low <= high){
		int mid = (low + high) / 2;
		if(arr[mid].getPatientID() == id){
			return mid;
		}
		else if(arr[mid].getPatientID() < id){
			low = mid + 1;
		}
		else{
			high = mid - 1;
		}
	}
	return -1;
}
