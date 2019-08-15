/*
Dependency Inversion principle (COMPILES USING -std=c++17):

1.- High level modules should not depend on low level modules, instead both should depend on abstractions.
2.- Abstractions should not depend on the details, details should depend on abstractions.

Generally, abstractions are represented as interfaces or base classes.
We do not want to depend on concrete classes, instead we should depend in classes as general as possible.
This way we do not depend on implementation details.
*/
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

// We want to model relationships between people

enum class Relationship
{
    parent,
    child,
    sibling
};

struct Person
{
    string name;
};

// Solves Research problems
struct RelationshipBrowser
{
    virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // low-level module
{
    vector<tuple<Person, Relationship, Person>> relations;

    void add_parent_andchild(const Person& parent, const Person& child)
    {
        relations.push_back({parent, Relationship::parent, child});
        relations.push_back({child, Relationship::parent, parent});
    }

    // Now any change in Relationships would have to comply to this function
    // This way, we can safely use it in Research
    vector<Person> find_all_children_of(const string& name) override {

        vector<Person> result;
        for (auto&& [first, rel, second] : relations)
        {
            if(first.name == name && rel == Relationship::parent)
            {
                result.push_back(second);
            }
        }
        return result;
    }
};

struct Research // high-level module
{
    // Bax example: Research should not depend on low-level modules
    // If Relationships struct decides to make its relations vector private, this breaks.
    // This could be solved by introducing an abstraction (interface)
    // Also, single responsibility principle would imply that getting the child of a given name should be part of Relationships
    /*
    Research(Relationships& relationships)
    {
        auto& relations = relationships.relations;

        for (auto&& [first, rel, second] : relations)
        {
            if(first.name == "John" && rel == Relationship::parent)
            {
                cout << "John has a child called " << second.name << '\n';
            }
        }
    }
    */

    Research(RelationshipBrowser& browser)
    {
        for (auto& child : browser.find_all_children_of("John"))
        {
            cout << "John has a child called " << child.name << '\n';
        }
    }
};

int main()
{
    Person parent{"John"};
    Person child1{"Chris"}, child2{"Matt"};

    Relationships relationships;
    relationships.add_parent_andchild(parent, child1);
    relationships.add_parent_andchild(parent, child2);

    Research _(relationships);  // This works because relationship inherits from RelationShipBrowser (polymorphism)

    return 0;
}