/*
Intersection between Composite and Proxy design patterns
*/
#include <iostream>
#include <algorithm>
#include <array>
#include <numeric>

// class Creature
// {
//     int strength, agility, intelligence;

//     //If we add another property we would need to rewrite aggregate functions

//     //We could have agregate storage for our fields

// public:
//     int get_strength() const {
//         return strength;
//     }

//     void set_strength(int strength) {
//         Creature::strength = strength;
//     }

//     int get_agility() const {
//         return agility;
//     }

//     void set_agility(int agility) {
//         Creature::agility = agility;
//     }

//     int get_intelligence() const {
//         return intelligence;
//     }

//     void set_intelligence(int intelligence) {
//         Creature::intelligence = intelligence;
//     }

//     // Aggregate calculations becomes painful
//     double sum() const {
//         return strength + agility + intelligence;
//     }

//     double avg() const {
//         return sum() / 3.0;
//     }

//     double max() const {
//         return std::max(std::max(strength, agility), intelligence);
//     }
// };

class Creature
{
    enum Abilities {
        strength,
        agility,
        intelligence,
        count
    };

    std::array<int, count> abilities;

public:

    int get_strength() const {return abilities[strength];}
    int set_strength(int value) {abilities[strength] = value;}

    int get_agility() const {return abilities[agility];}
    int set_agility(int value) {abilities[agility] = value;}

    int get_intelligence() const {return abilities[intelligence];}
    int set_ingelligence(int value) {abilities[intelligence] = value;}

    //aggregate functions now become easier

    double sum() const {
        return std::accumulate(abilities.begin(), abilities.end(), 0);
    }

    double average() const {
        return sum() / (double) count;
    }

    int max() const {
        return *std::max_element(abilities.begin(), abilities.end());
    }


};

int main(int ac, char* av[])
{

    Creature orc{};             //Initialize member variables {}
    orc.set_strength(16);
    orc.set_agility(11);
    orc.set_ingelligence(9);

    std::cout << "The orc has an average stat of "
        << orc.average()
        << " and a maximum stat of "
        << orc.max() << '\n';
    return 0;
}