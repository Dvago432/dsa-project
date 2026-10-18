#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include "Request.h"

class Queue {

    private:
        LinkedList<Request> requests;

    public:

        // Constructor and destructor
        Queue();
        ~Queue();

        // Prevent unsafe copying of the queue
        Queue(const Queue&) = delete;
        Queue& operator=(const Queue&) = delete;

        // Queue operations
        bool isEmpty() const;
        void enqueue(const Request& request);
        bool dequeue(Request& removedRequest);
        void display() const;
        int size() const;
};

#endif