
/*
More sophisticated implementation of chain of responsibility

Event broker -> Chain of Responsibility + Observer (boost:signals2) + Command Query Separation + mediator

*/
#include <iostream>
#include <string>

#include <boost/signals2.hpp>       //Send signals to classes

using namespace std;
using namespace boost;

// Take the Query something from game, take the signal, give it a query and invoke it;
// Query goes to every single suscriber
struct Query
{
    string creature_name;
    enum Argument {attack, defense} argument;
    int result;

    Query(const string& creature_name, Argument argument, int result)
        : creature_name{creature_name}, argument{argument}, result{result}
        {}
};

struct Game     //mediator
{
    signals2::signal<void(Query&)> queries;
};

class Creature
{
    Game& game;
    int attack, defense;
    

public:
    string name;
    Creature(Game& game, int attack, int defense, const string& name)
        : game{game}, attack{attack}, defense{defense}, name{name}
        {}
    
    int get_attack() const
    {
        Query q{name, Query::Argument::attack, attack};             //attack gives the initial value before modifiers
        game.queries(q);

        return q.result;
    }

    friend ostream& operator<<(ostream &os, const Creature& creature) {
        os << "attack: " << creature.get_attack()
            << " name: " << creature.name;

        return os;
    }
};

class CreatureModifier
{
    Game& game;
    Creature& creature;
public:
    CreatureModifier(Game& game, Creature& creature)
        : game{game}, creature{creature}
        {}
    virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
    signals2::connection conn;
public:
    DoubleAttackModifier(Game& game, Creature& creature)
        : CreatureModifier(game, creature)
    {
        conn = game.queries.connect([&](Query& q) {

            // Listen to game queries, if someone queries for the attack of our creature double the result
            if(q.creature_name == creature.name && 
                q.argument == Query::Argument::attack) 
            {
                q.result *= 2;
            }
        });
    };

    // Unsuscribe on destructor
    ~DoubleAttackModifier() {
        conn.disconnect();
    }
};

int main(int argc, char* argv[])
{

    Game game;
    Creature goblin{game, 2, 2, "Strong Goblin"};

    cout << goblin << '\n';

    //Temporary apply double attack modifier
    {
        DoubleAttackModifier dam{game, goblin};
        cout << goblin << '\n';
    } // After exiting scope DoubleAttackModifier is destroyed, thus unsuscribing;

    cout << goblin << '\n';

    return 0;
}