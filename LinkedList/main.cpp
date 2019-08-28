#include <iostream>

#include "LinkedList.hpp"

using std::cout;

int main() {
    cout << "Hello World!" << '\n';

    LinkedList myList{};
    myList.print();

    myList.insert(1);
    myList.insert(5);
    myList.insert(10);
    myList.insert(1);
    myList.insert(100);
    myList.insert(50);

    myList.sort();
    myList.print();
    return 0;
}