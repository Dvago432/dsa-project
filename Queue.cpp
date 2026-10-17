#include <iostream>
#include "Queue.h"

using namespace std;

// Constructor
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    count = 0;
}

// Destructor
Queue::~Queue() {
    Node* current = front;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    front = nullptr;
    rear = nullptr;
    count = 0;
}

// Check if queue is empty
bool Queue::isEmpty() const {
    return front == nullptr;
}

// Add a request to the rear
void Queue::enqueue(const Request& request) {
    Node* newNode = new Node(request);

    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    count++;

    cout << "Request added successfully." << endl;
}

// Remove a request from the front
bool Queue::dequeue(Request& removedRequest) {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return false;
    }

    Node* temp = front;

    removedRequest = temp->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    count--;

    cout << "Request processed successfully." << endl;

    return true;
}

// Display all requests
void Queue::display() const {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return;
    }

    Node* current = front;

    cout << "\n--- Admission Request Queue ---\n";

    while (current != nullptr) {
        current->data.displayRequest();
        current = current->next;
    }
}

// Return number of requests
int Queue::size() const {
    return count;
}