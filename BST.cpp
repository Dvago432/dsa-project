#include "BST.h"
#include <iostream>

using namespace std;

// Constructor
BST::BST() {
    root = nullptr;
}

// Destructor helper - post-order deletion (No STL needed)
void BST::destroyTree(BST_Node* current) {
    if (current == nullptr) return;
    destroyTree(current->left);
    destroyTree(current->right);
    delete current;
}

// Destructor
BST::~BST() {
    destroyTree(root);
    root = nullptr;
}

// Check if BST is empty
bool BST::isEmpty() const {
    return root == nullptr;
}

// Recursive insert by patientID
void BST::insert(BST_Node*& current, const Patient& patient) {
    if (current == nullptr) {
        current = new BST_Node(patient);
        return;
    }

    if (patient.getPatientID() < current->patient.getPatientID()) {
        insert(current->left, patient);
    } else if (patient.getPatientID() > current->patient.getPatientID()) {
        insert(current->right, patient);
    } else {
        // If patient ID already exists, update record
        current->patient = patient;
    }
}

// Insert patient wrapper
void BST::insertPatient(const Patient& patient) {
    insert(root, patient);
}

// Recursive search
bool BST::search(BST_Node* current, int target_id) const {
    if (current == nullptr) return false;

    if (target_id == current->patient.getPatientID()) {
        return true;
    } else if (target_id < current->patient.getPatientID()) {
        return search(current->left, target_id);
    } else {
        return search(current->right, target_id);
    }
}

bool BST::searchForPatient(int target_id) const {
    return search(root, target_id);
}

// Search and return pointer to patient
Patient* BST::searchNode(BST_Node* current, int target_id) {
    if (current == nullptr) return nullptr;

    if (target_id == current->patient.getPatientID()) {
        return &(current->patient);
    } else if (target_id < current->patient.getPatientID()) {
        return searchNode(current->left, target_id);
    } else {
        return searchNode(current->right, target_id);
    }
}

Patient* BST::getPatient(int target_id) {
    return searchNode(root, target_id);
}

// Standard BST node deletion
BST_Node* BST::deleteNode(BST_Node* current, int target_id, bool& deleted) {
    if (current == nullptr) return nullptr;

    if (target_id < current->patient.getPatientID()) {
        current->left = deleteNode(current->left, target_id, deleted);
    } else if (target_id > current->patient.getPatientID()) {
        current->right = deleteNode(current->right, target_id, deleted);
    } else {
        // Node found
        deleted = true;

        // Case 1 & 2: 0 or 1 child
        if (current->left == nullptr) {
            BST_Node* temp = current->right;
            delete current;
            return temp;
        } else if (current->right == nullptr) {
            BST_Node* temp = current->left;
            delete current;
            return temp;
        }

        // Case 3: 2 children - find inorder successor (smallest in right subtree)
        BST_Node* succ = current->right;
        while (succ->left != nullptr) {
            succ = succ->left;
        }

        // Copy successor data to current node
        current->patient = succ->patient;

        // Delete successor node from right subtree
        current->right = deleteNode(current->right, succ->patient.getPatientID(), deleted);
    }
    return current;
}

// Delete patient wrapper
void BST::deletePatient(int target_id) {
    if (root == nullptr) {
        cout << "BST is empty. Cannot delete." << endl;
        return;
    }

    bool deleted = false;
    root = deleteNode(root, target_id, deleted);

    if (deleted) {
        cout << "Patient with ID " << target_id << " successfully deleted from BST." << endl;
    } else {
        cout << "Patient with ID " << target_id << " not found in BST." << endl;
    }
}

// Inorder traversal (Left, Root, Right) -> sorted by patient ID
void BST::inorder(const BST_Node* current) const {
    if (current == nullptr) return;

    inorder(current->left);
    current->patient.display();
    inorder(current->right);
}

void BST::inorder_traverse() const {
    if (root == nullptr) {
        cout << "BST is empty." << endl;
        return;
    }
    cout << "\n--- BST Inorder Traversal (Sorted by ID) ---\n";
    inorder(root);
}

// Preorder traversal (Root, Left, Right)
void BST::preorder(const BST_Node* current) const {
    if (current == nullptr) return;

    current->patient.display();
    preorder(current->left);
    preorder(current->right);
}

void BST::preorder_traverse() const {
    if (root == nullptr) {
        cout << "BST is empty." << endl;
        return;
    }
    cout << "\n--- BST Preorder Traversal ---\n";
    preorder(root);
}

// Level-order traversal using custom array queue (No STL queue)
void BST::levelOrder(const BST_Node* current) const {
    if (current == nullptr) {
        cout << "BST is empty." << endl;
        return;
    }

    // Queue of BST node pointers with fixed safe capacity
    const int MAX_Q = 300;
    const BST_Node* q[MAX_Q];
    int front = 0;
    int rear = 0;

    q[rear++] = current;

    cout << "\n--- BST Level-Order Traversal ---\n";
    while (front < rear) {
        const BST_Node* node = q[front++];
        node->patient.display();

        if (node->left != nullptr && rear < MAX_Q) {
            q[rear++] = node->left;
        }
        if (node->right != nullptr && rear < MAX_Q) {
            q[rear++] = node->right;
        }
    }
}

void BST::levelOrder_traverse() const {
    levelOrder(root);
}
