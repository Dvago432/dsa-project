#include "Sorting.h"

long sortComparisons = 0;

// true if a must come before b
bool comesBefore(const Patient& a, const Patient& b, int criteria){
	sortComparisons++;

	if(criteria == BY_ID){
		return a.getPatientID() < b.getPatientID();
	}
	else if(criteria == BY_NAME){
		return a.getName() < b.getName();
	}
	else if(criteria == BY_DATE){
		Date d1 = a.getDate();
		Date d2 = b.getDate();
		if(d1.year != d2.year){
			return d1.year < d2.year;
		}
		if(d1.month != d2.month){
			return d1.month < d2.month;
		}
		return d1.day < d2.day;
	}
	else{
		return a.getPriority() < b.getPriority();
	}
}

Patient* listToArray(LinkedList<Patient>& list, int& n){
	n = list.getSize();
	Patient* arr = new Patient[n];

	Node<Patient>* temp = list.getHead();
	int i = 0;
	while(temp != NULL){
		arr[i] = temp->data;
		temp = temp->next;
		i++;
	}
	return arr;
}

void insertionSort(Patient arr[], int n, int criteria){
	for(int i = 1; i < n; i++){
		Patient key = arr[i];
		int j = i - 1;

		while(j >= 0 && comesBefore(key, arr[j], criteria)){
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void mergeParts(Patient arr[], int left, int mid, int right, int criteria){
	int total = right - left + 1;
	Patient* temp = new Patient[total];

	int i = left;
	int j = mid + 1;
	int k = 0;

	while(i <= mid && j <= right){
		if(comesBefore(arr[j], arr[i], criteria)){
			temp[k] = arr[j];
			j++;
		}
		else{
			temp[k] = arr[i];
			i++;
		}
		k++;
	}
	while(i <= mid){
		temp[k] = arr[i];
		i++;
		k++;
	}
	while(j <= right){
		temp[k] = arr[j];
		j++;
		k++;
	}

	for(int x = 0; x < total; x++){
		arr[left + x] = temp[x];
	}
	delete[] temp;
}

void mergeSort(Patient arr[], int left, int right, int criteria){
	if(left < right){
		int mid = (left + right) / 2;
		mergeSort(arr, left, mid, criteria);
		mergeSort(arr, mid + 1, right, criteria);
		mergeParts(arr, left, mid, right, criteria);
	}
}