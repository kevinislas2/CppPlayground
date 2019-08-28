#include "LinkedList.hpp"

#include <iostream>

using std::cout;

void LinkedList::print() {
    cout << "LinkedList::print()\n";
    Node* iterator = head;
    while(iterator) {
        std::cout << iterator->value << "->";
        iterator = iterator->next;
    }
    std::cout << '\n';
}

void LinkedList::insert(int i) {
    cout << "LinkedList::insert()\n";
    if(!head) {
        head = new Node(i);
    } else {

        Node* iterator = head;
        while(iterator->next) {
            iterator = iterator->next;
        }
        iterator->next = new Node(i);
    }
}

Node* LinkedList::search(int i) {
    cout << "LinkedList::search()\n";

    Node* iterator = head;
    while(iterator) {
        if(iterator->value == i) {
            std::cout << i << " found \n";
            return iterator;
        }

        iterator = iterator->next;
    }
    std::cout << i << " not found \n";
    return nullptr;
}

bool LinkedList::deleteNode(int i) {
    
    if(!head) {
        return false;
    }
    if(head->value == i) {
        Node* temp = head->next;
        delete head;
        head = temp;
    } else {
        Node* iterator = head;
        while(iterator->next) {
            if(iterator->next->value == i) {
                Node* temp = iterator->next->next;
                delete iterator->next;
                iterator->next = temp;
                return true;
            } else {
                iterator = iterator->next;
            }
        }

        return false;
    }
}

void LinkedList::sort() {
    cout << "LinkedList::sort()\n";
    Node* iterator = head;
    while(iterator) {
        Node* iterator2 = iterator->next;

        while(iterator2) {
            if(iterator2->value < iterator->value) {
                int temp = iterator->value;

                iterator->value = iterator2->value;
                iterator2->value = temp;
            }
            iterator2 = iterator2->next;
        }
        iterator = iterator->next;
    }
}
