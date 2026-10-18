#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "LinkedList.h"
#include "Request.h"

template <typename T>
class Queue {

    private:
        LinkedList<T> queue;

    public:

        // Constructor and destructor
        Queue();
        ~Queue();

        // Prevent unsafe copying of the queue
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        // Queue operations
        bool isEmpty() const;
        void enqueue(const T& item);
        bool dequeue(T& removedItem);
        void display() const;
        int size() const;
};

template <typename T>
Queue<T>::Queue() {
}

template <typename T>
Queue<T>::~Queue() {
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return queue.isEmpty();
}

template <typename T>
void Queue<T>::enqueue(const T& item) {
    queue.insertEnd(item);
    cout << "Request added successfully." << endl;
}

template <typename T>
bool Queue<T>::dequeue(T& removedItem) {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return false;
    }

    T* frontItem = queue.getAt(0);
    removedItem = *frontItem;
    queue.deleteFront();

    cout << "Request processed successfully." << endl;
    return true;
}
template <typename T>
void Queue<T>::display() const {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return;
    }

    cout << "\n--- Admission Request Queue ---\n";

    for (int i = 0; i < queue.getSize(); i++) {
        T* item = queue.getAt(i);
        if (item != nullptr) {
            item->displayRequest();
        }
    }
}

template <typename T>
int Queue<T>::size() const {
    return queue.getSize();
}
#endif