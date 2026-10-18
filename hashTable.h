#ifndef HASHTABLE_H
#define HASHTABLE_H

//IDs stored as strings; enumerate characters with ASCII equivalent
//table holds pointers to data

template<typename T>
struct hashNode {

    T data;
    hashNode<T>* next;
};

template<typename T>
class hashTable {

    private:
    //table of pointers

    hashNode<T>** HashTable;
    int size; // for mod

    int hash(const string& key) {

        int sum = 0;
        for (char c : key) sum = (sum*31 + c) % size;
        return sum;
    };
    public:

    hashTable(int size) : size(size) {

        HashTable = new hashNode<T>*[size];
        //nullify pointers

        for (int i = 0;i < size; i++) HashTable[i] == nullptr;
    }
    T* get(const string& key) {

        int index = hash(key);
        hashNode* found = HashTable[index];
        return found->data;
    }
    void insert(const string& key, T* data) {

        int index = hash(key);
        hashNode* newNode = new hashNode(data);
        HashTable[index] = newNode;
    }
    void remove(const string& key) {

        int index = hash(key);
    }
};
#endif