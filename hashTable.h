#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
using namespace std;

template<typename T>
struct hashNode {

    string key;
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

        for (int i = 0;i < size; i++) HashTable[i] = nullptr;
    }
    T* get(const string& key) {

        int index = hash(key);
        hashNode<T>* found = HashTable[index];
        while (found != nullptr) {
            if (found->key == key) return &found->data;
            found = found->next;
        }
        return nullptr;
    }
    void insert(const string& key, T data) {

        int index = hash(key);
        hashNode<T>* newNode = new hashNode<T>;
        newNode->key = key;
        newNode->data = data;
        newNode->next = HashTable[index];
        HashTable[index] = newNode;
    }
    void remove(const string& key) {

        int index = hash(key);
    }
};
#endif