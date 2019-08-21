/*
Example from the original GoF book

Sort of an artificial example
Modern implementations might store Modifiers on a vector inside the creature itself
*/
#include <iostream>
#include <string>

using namespace std;

struct Creature
{
    string name;
    int attack, defense;

    Creature(const string& name, int attack, int defense)
        : name{name}, attack{attack}, defense{defense}
        {}

    friend ostream& operator<<(ostream& os, const Creature& creature) {
        os << "name: " << creature.name << " attack: " << creature.attack
            << " defense: " << creature.defense;

        return os;
    }
};

// A single linked list
class CreatureModifier
{
    // This allows us to chain CreatureModifiers
    CreatureModifier* next{nullptr};

protected:
    Creature& creature;

public:
    CreatureModifier(Creature& creature)
        : creature{creature}
        {}
    
    void add(CreatureModifier *cm)
    {
        // Add to end of single linked list
        if (next) {
            next->add(cm);
        } else {
            next = cm;
        }
    }

    // Meant to be overriden, but we want to keep that each modifier calls the next
    // in the chain of responsibility
    virtual void handle()
    {
        if (next) next->handle();
    }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
    DoubleAttackModifier(Creature& creature)
        : CreatureModifier(creature)
        {}

    void handle() override {
        creature.attack *= 2;
        CreatureModifier::handle();     // Call to base class handle function (calling next in chain of responsibility)
    }
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
    IncreaseDefenseModifier(Creature& creature)
        : CreatureModifier{creature}
        {}

    void handle() override {
        if (creature.attack <= 2) {
            creature.defense++;
        }
        CreatureModifier::handle();
    }
};

//Cancel all the modifiers
class NoBonusesModifier : public CreatureModifier
{
public:
    NoBonusesModifier(Creature& creature)
        : CreatureModifier(creature)
        {}
    
    void handle() override {

    }
};

int main()
{

    Creature goblin{"Goblin", 1, 1};
    CreatureModifier root{goblin};          //Root of modifiers (doesnt affect creature)
    DoubleAttackModifier r1{goblin};
    DoubleAttackModifier r1_2{goblin};
    IncreaseDefenseModifier r2{goblin};

    // Curse fails to propagate the subsecuent calls of the modifiers
    // However, this relies on curse being added first to the list
    // Perhaps a better approach would be to implement a remove() operation
    // On each modifier which cancels the effect of the modifier and removes it from the list
    // Another useful thing might be to selectively apply the modifiers via a bool flag
    // This way, modifiers can be canceled without being removed from the list
    NoBonusesModifier curse{goblin};
    root.add(&curse);

    root.add(&r1);      //attack = 2
    root.add(&r1_2);    //attack = 4
    root.add(&r2);          //By the time we invoke this modifier attack will be greater than 2, thus not affecting the monster's defense

    root.handle();      // Applies chain of responsibility
    //root.handle();    // Each call to handle re-applies all the modifiers

    cout << goblin << '\n';

    return 0;
}