#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

class Node {
public:
    int value;
    Node* next;

    Node(int value) : value{value}, next{nullptr} {
        std::cout << "Node constructor \n"; 
    };

    ~Node() {
        std::cout << "Node destructor \n";
    }
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head{nullptr} {};
    ~LinkedList() {
        Node* iterator = head;
        while(iterator) {
            Node* next = iterator->next;
            delete iterator;
            iterator = next;
        }
    }

    void insert(int i);
    bool deleteNode(int i);
    Node* search(int i);
    void print();
    void sort();
};
#endif