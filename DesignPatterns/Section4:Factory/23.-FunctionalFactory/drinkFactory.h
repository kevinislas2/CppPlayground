#ifndef DRINK_FACTORY_H
#define DRINK_FACTORY_H

#include <map>
#include <functional>

using namespace std;

#include "hotDrink.h"
#include "hotDrinkFactory.h"

class DrinkFactory
{
    map<string, unique_ptr<HotDrinkFactory>> hot_factories;

public:
    DrinkFactory()
    {
        hot_factories["coffee"] = make_unique<CoffeeFactory>();
        hot_factories["tea"] = make_unique<TeaFactory>();
    }

    unique_ptr<HotDrink> make_drink(const string& name)
    {
        auto drink = hot_factories[name]->make();
        drink->prepare(200);
        return drink;
    }
};

//Instead of mapping string, pointer we map it to an annonymous function
class DrinkWithVolumeFactory
{
    map<string, function<unique_ptr<HotDrink>()>> factories;
public:
    DrinkWithVolumeFactory()
    {
        factories["tea"] = [] {
            auto tea = make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories["coffee"] = [] {
            auto coffee = make_unique<Coffee>();
            coffee->prepare(200);
            return coffee;
        };
    }

    unique_ptr<HotDrink> make_drink(const string& name) {
        return factories[name]();
    }
};

#endif