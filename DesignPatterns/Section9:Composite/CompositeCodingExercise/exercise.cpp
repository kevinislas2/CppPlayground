#include "exercise.h"

int sum(const vector<ContainsIntegers*> items)
{
    int result = 0;
    for(auto item: items) { // item is a pointer to containsIntegers
        result += item->sum();
    }
    return result;
}