#include <iostream>
#include "Stack.h"

using namespace std;

// UndoAction default constructor
UndoAction::UndoAction() {
    actionType = "";
    patientID = "";
    previousStatus = "";
    previousWard = "";
}

// UndoAction parameterized constructor
UndoAction::UndoAction(const string& actionType,
                       const string& patientID,
                       const string& previousStatus,
                       const string& previousWard) {
                       	
    this->actionType = actionType;
    this->patientID = patientID;
    this->previousStatus = previousStatus;
    this->previousWard = previousWard;
}

// Node constructor
Stack::Node::Node(const UndoAction& action){

    data=action;
	next=nullptr;
}
// Stack constructor
Stack::Stack() {
    topNode = nullptr;
    count = 0;
}

// Stack destructor
Stack::~Stack() {
    while (topNode != nullptr) {
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    count = 0;
}

// Check if the stack is empty
bool Stack::isEmpty() const {
    return topNode == nullptr;
}

// Add an action to the top
void Stack::push(const UndoAction& action) {
    Node* newNode = new Node(action);

    newNode->next = topNode;
    topNode = newNode;

    count++;

    cout << "Undo action saved successfully." << endl;
}

// Remove the top action
bool Stack::pop(UndoAction& removedAction) {
    if (isEmpty()) {
        cout << "The stack is empty." << endl;
        return false;
    }

    Node* temp = topNode;

    removedAction = temp->data;
    topNode = topNode->next;

    delete temp;
    count--;

    return true;
}

// View the top action without removing it
bool Stack::peek(UndoAction& topAction) const {
    if (isEmpty()) {
        return false;
    }

    topAction = topNode->data;
    return true;
}

// Display all actions
void Stack::display() const {
    if (isEmpty()) {
        cout << "The stack is empty." << endl;
        return;
    }

    Node* current = topNode;

    cout << "\n--- Undo Stack ---\n";

    while (current != nullptr) {
        cout << "Action: " << current->data.actionType << endl;
        cout << "Patient ID: " << current->data.patientID << endl;
        cout << "Previous Status: "
             << current->data.previousStatus << endl;
        cout << "Previous Ward: "
             << current->data.previousWard << endl;
        cout << "------------------\n";

        current = current->next;
    }
}

// Return the number of actions
int Stack::size() const {
    return count;
}