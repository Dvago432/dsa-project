#include <iostream>
#include "Queue.h"

using namespace std;

// Constructor
Queue::Queue() {
}

// Destructor
Queue::~Queue() {
}

// Check if queue is empty
bool Queue::isEmpty() const {
    return requests.isEmpty();
}

// Add a request to the rear
void Queue::enqueue(const Request& request) {
    requests.insertEnd(request);
    cout << "Request added successfully." << endl;
}

// Remove a request from the front
bool Queue::dequeue(Request& removedRequest) {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return false;
    }

    Request* frontRequest = requests.getAt(0);
    if (frontRequest == nullptr) {
        cout << "The queue is empty." << endl;
        return false;
    }

    removedRequest = *frontRequest;
    requests.deleteFront();

    cout << "Request processed successfully." << endl;
    return true;
}

// Display all requests
void Queue::display() const {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return;
    }

    cout << "\n--- Admission Request Queue ---\n";

    for (int i = 0; i < requests.getSize(); i++) {
        Request* request = requests.getAt(i);
        if (request != nullptr) {
            request->displayRequest();
        }
    }
}

// Return number of requests
int Queue::size() const {
    return requests.getSize();
}