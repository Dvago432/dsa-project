#ifndef STACK_H
#define STACK_H

#include <string>
using namespace std;

struct UndoAction {
    string actionType;
    string patientID;
    string previousStatus;
    string previousWard;

    UndoAction();
    UndoAction(const string& actionType,
               const string& patientID,
               const string& previousStatus,
               const string& previousWard);
};

class Stack {
    private:
    	struct Node {
        UndoAction data;
        Node* next;

        Node(const UndoAction& action);
        };
    	
    

        Node* topNode;
        int count;

    public:
    	
    	Stack();
        ~Stack();

        Stack(const Stack&) = delete;
        Stack& operator=(const Stack&) = delete;

        bool isEmpty() const;
        void push(const UndoAction& action);
        bool pop(UndoAction& removedAction);
        bool peek(UndoAction& topAction) const;
        void display() const;
        int size() const;
    
};

#endif