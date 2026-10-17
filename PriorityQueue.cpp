#include <iostream>
#include "PriorityQueue.h"

using namespace std;

// Constructor
PriorityQueue::PriorityQueue() {
    capacity = 5;
    count = 0;

    heap = new Request[capacity];
}

// Destructor
PriorityQueue::~PriorityQueue() {
    delete[] heap;
    heap = nullptr;

    capacity = 0;
    count = 0;
}
 
// Check if the heap is empty
bool PriorityQueue::isEmpty() const {
    return count == 0;
}

// Return number of requests
int PriorityQueue::size() const {
    return count;
}

// Increase array capacity
void PriorityQueue::resize() {
    int newCapacity = capacity * 2;

    Request* newHeap = new Request[newCapacity];

    for (int i = 0; i < count; i++) {
        newHeap[i] = heap[i];
    }

    delete[] heap;

    heap = newHeap;
    capacity = newCapacity;
}

// Move a request upwards
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap[index].getPriority() <
            heap[parent].getPriority()) {

            Request temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            index = parent;
        } else {
            break;
        }
    }
}

// Move a request downwards
void PriorityQueue::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        int smallest = index;

        if (left < count &&
            heap[left].getPriority() <
            heap[smallest].getPriority()) {

            smallest = left;
        }

        if (right < count &&
            heap[right].getPriority() <
            heap[smallest].getPriority()) {

            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        Request temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;

        index = smallest;
    }
}

// Insert a request
void PriorityQueue::insert(const Request& request) {
    if (count == capacity) {
        resize();
    }

    heap[count] = request;

    heapifyUp(count);

    count++;

    cout << "Request added to Priority Queue." << endl;
}

// Remove the highest-priority request
bool PriorityQueue::removeHighestPriority(
    Request& removedRequest) {

    if (isEmpty()) {
        cout << "Priority Queue is empty." << endl;
        return false;
    }

    removedRequest = heap[0];

    heap[0] = heap[count - 1];

    count--;

    if (count > 0) {
        heapifyDown(0);
    }

    cout << "Highest-priority request removed." << endl;

    return true;
}

// View highest-priority request
bool PriorityQueue::peek(
    Request& highestPriorityRequest) const {

    if (isEmpty()) {
        return false;
    }

    highestPriorityRequest = heap[0];

    return true;
}

// Display requests in heap-array order
void PriorityQueue::display() const {
    if (isEmpty()) {
        cout << "Priority Queue is empty." << endl;
        return;
    }

    cout << "\n--- Priority Queue ---\n";

    for (int i = 0; i < count; i++) {
        heap[i].displayRequest();
    }
}