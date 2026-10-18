#include "BST.h"
#include <iostream>
using namespace std;
//come back to destructor

void BST::insert(BST_Node* current, const Patient& patient) {

    if (current == nullptr) {

        current = new BST_Node;
        current->patient = patient;
        return;
    }

    if (patient.getPatientID() < current->patient.getPatientID()) {

        insert(current->left, patient);
    }
    if (patient.getPatientID() > current->patient.getPatientID()) {

        insert(current->right, patient);
    }
}
void BST::preorder(const BST_Node* current) const {

    if (current == nullptr) return;
    
    cout << current->patient.getName();
    cout << ": ";
    cout << current->patient.getAge();
    cout << ": ";
    cout << current->patient.getCondition();
    cout << ": ";
    cout << current->patient.getAssignedWard();
    cout << ": ";
    cout << current->patient.getPriority();
    cout << ": ";
    cout << current->patient.getStatus();
    preorder(current->left);
    preorder(current->right);
}

void BST::levelOrder(const BST_Node* current) const {

    if (current == nullptr) return;
    
}

void BST::inorder(const BST_Node* current) const {

    if (current == nullptr) return;
    inorder(current->left);
    cout << current->patient.getName();
    cout << ": ";
    cout << current->patient.getAge();
    cout << ": ";
    cout << current->patient.getCondition();
    cout << ": ";
    cout << current->patient.getAssignedWard();
    cout << ": ";
    cout << current->patient.getPriority();
    cout << ": ";
    cout << current->patient.getStatus();
    inorder(current->right);
}

bool BST::search(BST_Node* current, int target) {

    if (current == nullptr) return false;
    if (target < current->patient.getPatientID()) {

        return search(current->left, target);
    }

    if (target > current->patient.getPatientID()) {

        return search(current->right, target);
    }

    if (target == current->patient.getPatientID()) {

        return true;
    }

    return false;
}
void BST::insertPatient(Patient patient_) {

    insert(root, patient_);
}

bool BST::searchForPatient(int target_id) {

    return search(root, target_id);
}

void BST::deletePatient(int target_id) {

    if (root == nullptr) return;
    bool found = searchForPatient(target_id);

    if (found) {

        BST_Node* temp = root->left;
        BST_Node* temp2 = root->right;
        temp2->left = temp;
        temp->right = temp2;
        delete root;

    } else cout << "No such patient exists";
}
//might need fixing; changing the root is inefficient

void BST::inorder_traverse() {

    inorder(root);
}