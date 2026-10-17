#include "BST.h"
#include <iostream>
using namespace std;

BST::BST() {

    root->left = nullptr;
    root->right = nullptr;
    root = nullptr;
    count = 0;
}

//come back to destructor
void BST::insertPatient(Patient patient_) {

    if (root == nullptr) {

        root->patient = patient_;
        return;
    }

    if (patient_.getPatientID() < root->patient.getPatientID()) {

        root = root->left;
        insertPatient(patient_);
    }

    if (patient_.getPatientID() > root->patient.getPatientID()) {

        root = root->right;
        insertPatient(patient_);
    }
}

bool BST::searchForPatient(int target_id) {

    if (target_id == root->patient.getPatientID()) {

        return true;
    }

    if (target_id < root->patient.getPatientID()) {

        root = root->left;
        count++;
        return searchForPatient(target_id);
    }

    if (target_id > root->patient.getPatientID()) {

        root = root->right;
        count++;
        return searchForPatient(target_id);
    }

    return false;
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

    BST_Node* current = root;

    current = current->left;
    inorder_traverse();

    cout << current->patient.getName();
    cout << ": ";
    cout << current->patient.getAge();
    cout << ": ";
    cout << current->patient.getCondition();
    cout << ": ";
    cout << current->patient.getAssignedWard();

}