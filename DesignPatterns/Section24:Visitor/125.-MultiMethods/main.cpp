/*
Multimethods
Extends Double Dispatch
Overloads of two argument functions
In this example we perform double dispatch with multiple arguments (no visitor method)

Example: Collisions in space
*/

#include <iostream>
#include <string>
#include <sstream>
#include <typeindex>
#include <map>
#include <utility>

using namespace std;

struct GameObject;

void collide(GameObject& first, GameObject& second);

struct GameObject
{
    virtual type_index type() const = 0;

    virtual void collide(GameObject& other)
    {
        ::collide(*this, other);
    }
};

//CRTP  (Curiously Recurrent Template Pattern)
template <typename T> 
struct GameObjectImpl : GameObject
{
    type_index type() const override {
        return typeid(T);
    }
};

struct Planet : GameObjectImpl<Planet> {

};

struct Asteroid : GameObjectImpl<Asteroid> {

};

struct Spaceship : GameObjectImpl<Spaceship> {

};

void spaceship_planet() {
    cout << "Spaceship lands on a planet \n";
}

void asteroid_planet() {
    cout << "Asteroid burns up in the atmosphere\n";
}

void asteroid_ship() {
    cout << "Asteroid hits and destroys spaceship\n";
}

//Map pair of type_index to function that returns void and takes void
map<pair<type_index, type_index>, void(*)(void)>  outcomes {
    {{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
    {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
    {{typeid(Asteroid), typeid(Spaceship)}, asteroid_ship},
};

void collide(GameObject& first, GameObject& second) {
    auto it = outcomes.find({first.type(), second.type()});

    if (it == outcomes.end()) {
        it = outcomes.find({second.type(), first.type()});

        if (it == outcomes.end()) {
            cout << "objects pass each other harmlessly\n";
            return;
        }
    }

    it->second();       //calls the function

}

int main()
{
    Asteroid asteroid;
    Planet planet;
    Spaceship spaceship;

    collide(planet, spaceship);
    collide(planet, asteroid);
    collide(spaceship, asteroid);
    collide(planet, planet);

    return 0;
}