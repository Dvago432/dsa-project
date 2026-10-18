#ifndef BST_H
#define BST_H

#include "patient.h"
//Use patient id to search, insert and delete patients by id
//use custom node

class BST {

    private:

        BST_Node* root;
        int count;

    public:

        BST(); //constructor
        ~BST(); //destructor
        void insertPatient(Patient);
        bool searchForPatient(int); //search by ID
        void deletePatient(int);
        void inorder_traverse();
        void preorder_traverse();
        void levelOrder_traverse();
};
#endif