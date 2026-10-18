#ifndef BST_H
#define BST_H
#include "LinkedList.h"
#include "patient.h"
//Use patient id to search, insert and delete patients by id
//use custom node

struct BST_Node {

    Patient patient;
    BST_Node* left;
    BST_Node* right;
};
class BST {

    private:

        BST_Node* root;
        void insert(BST_Node*, const Patient&);
        void inorder(const BST_Node*) const;
        bool search(BST_Node*, int);
        void preorder(const BST_Node*) const;
        void levelOrder(const BST_Node*) const;
    public:

        BST() : root(nullptr) {}; //constructor
        ~BST(); //destructor
        void insertPatient(Patient);
        bool searchForPatient(int); //search by ID
        void deletePatient(int);
        void inorder_traverse();
        void preorder_traverse();
        void levelOrder_traverse();
};
#endif