/*
g++ exercise.h exercise.cpp main.cpp -std=c++14 && ./a.out

Consider the code presented below. The sum() function takes a vector of pointers to either SingleValue or ManyValues instances
and adds up all their elements together.

Please complete the implementation so that the sum() function starts to operate correctly. This may involve giving the classes
a common interface, among other things

Heres is an example of how the function might be used:

SingleValue single_value { 1 };
ManyValues other_values;
other_values.add(2);
other_values.add(3);
sum({ &single_value, &other_values});   //returns 6

*/

#include <iostream>

#include "exercise.h"
int main() {

    SingleValue single_value { 1 };
    ManyValues other_values;
    other_values.add(2);
    other_values.add(3);

    std::cout << sum({ &single_value, &other_values}) << '\n';

    return 0;
}