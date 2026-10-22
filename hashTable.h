#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>

using namespace std;

// Node for separate chaining collision resolution
template <typename T>
struct HashNode {
    string key;
    T data;
    HashNode<T>* next;

    HashNode(const string& k, const T& d) : key(k), data(d), next(nullptr) {}
};

template <typename T>
class hashTable {
    private:
        HashNode<T>** table;
        int capacity;
        int count;

        // Custom polynomial rolling hash function
        int hashFunction(const string& key) const {
            long long hashValue = 0;
            for (char c : key) {
                hashValue = (hashValue * 31 + c) % capacity;
            }
            if (hashValue < 0) {
                hashValue += capacity;
            }
            return static_cast<int>(hashValue);
        }

    public:
        // Constructor
        hashTable(int cap = 101) : capacity(cap), count(0) {
            table = new HashNode<T>*[capacity];
            for (int i = 0; i < capacity; i++) {
                table[i] = nullptr;
            }
        }

        // Destructor
        ~hashTable() {
            clear();
            delete[] table;
            table = nullptr;
        }

        // Prevent copying
        hashTable(const hashTable&) = delete;
        hashTable& operator=(const hashTable&) = delete;

        // Clear all entries
        void clear() {
            for (int i = 0; i < capacity; i++) {
                HashNode<T>* current = table[i];
                while (current != nullptr) {
                    HashNode<T>* temp = current;
                    current = current->next;
                    delete temp;
                }
                table[i] = nullptr;
            }
            count = 0;
        }

        // Insert or update
        void insert(const string& key, const T& data) {
            int index = hashFunction(key);

            // Check if key already exists, update data if found
            HashNode<T>* current = table[index];
            while (current != nullptr) {
                if (current->key == key) {
                    current->data = data;
                    return;
                }
                current = current->next;
            }

            // Insert new node at head of chain
            HashNode<T>* newNode = new HashNode<T>(key, data);
            newNode->next = table[index];
            table[index] = newNode;
            count++;
        }

        // Lookup (O(1) average time)
        T* get(const string& key) {
            int index = hashFunction(key);
            HashNode<T>* current = table[index];
            while (current != nullptr) {
                if (current->key == key) {
                    return &(current->data);
                }
                current = current->next;
            }
            return nullptr;
        }

        const T* get(const string& key) const {
            int index = hashFunction(key);
            HashNode<T>* current = table[index];
            while (current != nullptr) {
                if (current->key == key) {
                    return &(current->data);
                }
                current = current->next;
            }
            return nullptr;
        }

        // Remove entry
        bool remove(const string& key) {
            int index = hashFunction(key);
            HashNode<T>* current = table[index];
            HashNode<T>* prev = nullptr;

            while (current != nullptr) {
                if (current->key == key) {
                    if (prev == nullptr) {
                        table[index] = current->next;
                    } else {
                        prev->next = current->next;
                    }
                    delete current;
                    count--;
                    return true;
                }
                prev = current;
                current = current->next;
            }
            return false;
        }

        // Display all entries in the hash table
        void displayAll() const {
            if (count == 0) {
                cout << "Hash Table is empty." << endl;
                return;
            }

            cout << "\n--- Hash Table Contents (" << count << " items) ---\n";
            for (int i = 0; i < capacity; i++) {
                HashNode<T>* current = table[i];
                while (current != nullptr) {
                    cout << "[Bucket " << i << " | Key: " << current->key << "] ";
                    current->data.display();
                    current = current->next;
                }
            }
        }

        int size() const {
            return count;
        }

        bool isEmpty() const {
            return count == 0;
        }
};

#endif
