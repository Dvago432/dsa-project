#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using namespace std;

// Templates must be implemented in the header, so there is no LinkedList.cpp.
// One list class is reused for Patient, Ward and Equipment.

template <class T>
struct Node{

	T data;
	Node<T>* next;
};

template <class T>
class LinkedList{

	private:

		Node<T>* head;
		int size;

		// copying is switched off so two lists never share the same nodes
		LinkedList(const LinkedList& other);
		LinkedList& operator=(const LinkedList& other);

	public:

		LinkedList();
		~LinkedList();

		void insertFront(T item);
		void insertEnd(T item);
		bool insertAt(int pos, T item); //pos from 0 to size

		bool deleteFront();
		bool deleteEnd();
		bool deleteAt(int pos); //pos from 0 to size-1

		T* getAt(int pos); //NULL if pos is invalid
		Node<T>* getHead();
		int getSize();
		bool isEmpty();
		void clear();
};

template <class T>
LinkedList<T>::LinkedList(){
	head = NULL;
	size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
	clear();
}

template <class T>
void LinkedList<T>::insertFront(T item){
	Node<T>* newNode = new Node<T>;
	newNode->data = item;
	newNode->next = head;
	head = newNode;
	size++;
}

template <class T>
void LinkedList<T>::insertEnd(T item){
	Node<T>* newNode = new Node<T>;
	newNode->data = item;
	newNode->next = NULL;

	if(head == NULL){
		head = newNode;
	}
	else{
		Node<T>* temp = head;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = newNode;
	}
	size++;
}

template <class T>
bool LinkedList<T>::insertAt(int pos, T item){
	if(pos < 0 || pos > size){
		return false;
	}
	if(pos == 0){
		insertFront(item);
		return true;
	}

	Node<T>* temp = head;
	for(int i = 0; i < pos - 1; i++){
		temp = temp->next;
	}

	Node<T>* newNode = new Node<T>;
	newNode->data = item;
	newNode->next = temp->next;
	temp->next = newNode;
	size++;
	return true;
}

template <class T>
bool LinkedList<T>::deleteFront(){
	if(head == NULL){
		return false;
	}
	Node<T>* temp = head;
	head = head->next;
	delete temp;
	size--;
	return true;
}

template <class T>
bool LinkedList<T>::deleteEnd(){
	if(head == NULL){
		return false;
	}
	if(size == 1){
		return deleteFront();
	}

	Node<T>* temp = head;
	while(temp->next->next != NULL){
		temp = temp->next;
	}
	delete temp->next;
	temp->next = NULL;
	size--;
	return true;
}

template <class T>
bool LinkedList<T>::deleteAt(int pos){
	if(pos < 0 || pos >= size){
		return false;
	}
	if(pos == 0){
		return deleteFront();
	}

	Node<T>* temp = head;
	for(int i = 0; i < pos - 1; i++){
		temp = temp->next;
	}

	Node<T>* toDelete = temp->next;
	temp->next = toDelete->next;
	delete toDelete;
	size--;
	return true;
}

template <class T>
T* LinkedList<T>::getAt(int pos){
	if(pos < 0 || pos >= size){
		return NULL;
	}
	Node<T>* temp = head;
	for(int i = 0; i < pos; i++){
		temp = temp->next;
	}
	return &(temp->data);
}

template <class T>
Node<T>* LinkedList<T>::getHead(){
	return head;
}

template <class T>
int LinkedList<T>::getSize(){
	return size;
}

template <class T>
bool LinkedList<T>::isEmpty(){
	return size == 0;
}

template <class T>
void LinkedList<T>::clear(){
	while(head != NULL){
		deleteFront();
	}
}

#endif
