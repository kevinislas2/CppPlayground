/*
Families of factories
*/
#include <iostream>

using namespace std;

#include "hotDrinkFactory.h"
#include "drinkFactory.h"

unique_ptr<HotDrink> make_drink(string type)
{
    unique_ptr<HotDrink> drink;

    // Without the abstract factory we would need to check type with an if statement
    if(type == "tea")
    {
        drink = make_unique<Tea>();
        drink->prepare(200);
    } else {
        drink = make_unique<Coffee>();
        drink->prepare(50);
    }
    return drink;
}
int main()
{
    DrinkFactory df;
    auto c = make_drink("coffee");

    return 0;
}