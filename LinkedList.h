#ifndef LINKEDLIST_H
#define LINKEDLIST_H
// Templates must be implemented in the header, so there is no LinkedList.cpp.
// One list class is reused for Patient, Ward and Equipment.

template <class T>
struct Node{

	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <class T>
class LinkedList{

	private:

		Node<T>* head;
		Node<T>* tail;
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
		const T* getAt(int pos) const;
		Node<T>* getHead();
		const Node<T>* getHead() const;
		Node<T>* getTail();
		const Node<T>* getTail() const;
		int getSize() const;
		bool isEmpty() const;
		void clear();
};

template <class T>
LinkedList<T>::LinkedList(){
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
	clear();
}

template <class T>
void LinkedList<T>::insertFront(T item){
	Node<T>* newNode = new Node<T>{item, head, nullptr};
	if(head == nullptr){
		tail = newNode;
	}
	else{
		head->prev = newNode;
	}
	head = newNode;
	size++;
}

template <class T>
void LinkedList<T>::insertEnd(T item){
	Node<T>* newNode = new Node<T>{item, nullptr, tail};
	if(tail == nullptr){
		head = newNode;
	}
	else{
		tail->next = newNode;
	}
	tail = newNode;
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
	if(pos == size){
		insertEnd(item);
		return true;
	}

	Node<T>* temp = head;
	for(int i = 0; i < pos - 1; i++){
		temp = temp->next;
	}

	Node<T>* newNode = new Node<T>{item, temp->next, temp};
	temp->next->prev = newNode;
	temp->next = newNode;
	size++;
	return true;
}

template <class T>
bool LinkedList<T>::deleteFront(){
	if(head == nullptr){
		return false;
	}
	Node<T>* temp = head;
	head = head->next;
	if(head == nullptr){
		tail = nullptr;
	}
	else{
		head->prev = nullptr;
	}
	delete temp;
	size--;
	return true;
}

template <class T>
bool LinkedList<T>::deleteEnd(){
	if(head == nullptr){
		return false;
	}
	if(head == tail){
		return deleteFront();
	}
	Node<T>* temp = tail;
	tail = tail->prev;
	tail->next = nullptr;
	delete temp;
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

	if(pos == size - 1){
		return deleteEnd();
	}

	Node<T>* toDelete = head;
	if(pos <= size / 2){
		for(int i = 0; i < pos; i++){
			toDelete = toDelete->next;
		}
	}
	else{
		toDelete = tail;
		for(int i = size - 1; i > pos; i--){
			toDelete = toDelete->prev;
		}
	}
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;
	delete toDelete;
	size--;
	return true;
}

template <class T>
T* LinkedList<T>::getAt(int pos){
	if(pos < 0 || pos >= size){
		return nullptr;
	}
	Node<T>* temp = head;
	for(int i = 0; i < pos; i++){
		temp = temp->next;
	}
	return &(temp->data);
}

template <class T>
const T* LinkedList<T>::getAt(int pos) const{
	if(pos < 0 || pos >= size){
		return nullptr;
	}
	const Node<T>* temp = head;
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
const Node<T>* LinkedList<T>::getHead() const{
	return head;
}

template <class T>
Node<T>* LinkedList<T>::getTail(){
	return tail;
}

template <class T>
const Node<T>* LinkedList<T>::getTail() const{
	return tail;
}

template <class T>
int LinkedList<T>::getSize() const{
	return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const{
	return size == 0;
}

template <class T>
void LinkedList<T>::clear(){
	Node<T>* current = head;
	while(current != nullptr){
		Node<T>* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	tail = nullptr;
	size = 0;
}

#endif
