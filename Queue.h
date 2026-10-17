#ifndef QUEUE_H
#define QUEUE_H

#include "Request.h"

class Queue {
	
    private:
    	
        struct Node {
    	
            Request data;
            Node* next;

            Node(const Request& request){
            	
                data=request;
				next=nullptr;
            }
        };

        Node* front;
        Node* rear;
        int count;

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