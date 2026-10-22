#ifndef BST_H
#define BST_H

#include "Patient.h"

// BST Node for Patient records organised by PatientID
struct BST_Node {
    Patient patient;
    BST_Node* left;
    BST_Node* right;

    BST_Node(const Patient& p) : patient(p), left(nullptr), right(nullptr) {}
};

class BST {
    private:
        BST_Node* root;

        void insert(BST_Node*& current, const Patient& patient);
        void inorder(const BST_Node* current) const;
        void preorder(const BST_Node* current) const;
        void levelOrder(const BST_Node* current) const;
        bool search(BST_Node* current, int target_id) const;
        Patient* searchNode(BST_Node* current, int target_id);
        BST_Node* deleteNode(BST_Node* current, int target_id, bool& deleted);
        void destroyTree(BST_Node* current);

    public:
        BST();
        ~BST();

        // Prevent copying
        BST(const BST&) = delete;
        BST& operator=(const BST&) = delete;

        void insertPatient(const Patient& patient);
        bool searchForPatient(int target_id) const;
        Patient* getPatient(int target_id);
        void deletePatient(int target_id);

        void inorder_traverse() const;
        void preorder_traverse() const;
        void levelOrder_traverse() const;

        bool isEmpty() const;
};

#endif
