#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Request.h"

class PriorityQueue {
	private:
		
        Request* heap;
        int capacity;
        int count;

        void heapifyUp(int index);
        void heapifyDown(int index);
        void resize();

    public:
        // Constructor and destructor
        PriorityQueue();
       ~PriorityQueue();

        // Prevent accidental copying
        PriorityQueue(const PriorityQueue&) = delete;
        PriorityQueue& operator=(const PriorityQueue&) = delete;

        // Operations
        bool isEmpty() const;
        int size() const;

        void insert(const Request& request);

        bool removeHighestPriority(Request& removedRequest);
        bool peek(Request& highestPriorityRequest) const;

        void display() const;

};

#endif