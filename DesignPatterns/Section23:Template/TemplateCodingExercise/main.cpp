/*

Template Coding Exercise

Imagine a typical collectible card game which has cards representing creatures.
Each creature has two values: Attack and Health.

Creatures can fight each other, dealing their Attack damage,
thereby reducing their oppponent's health.

The class CardGame implements the logic for two creatures fighting one another.
However, the exact mechanics of how damage is dealt is different:

TemporaryCardDamage: In some cases (e.g., Magic: the Gathering), unless the
creature has been killed, its heald returns to the original value at the 
end of combat.

PermanentCardDamage: In other games (e.g., Hearthstone), health damage persists.

Your are asked to implement classes TemporaryCardDamage and PermanentCardDamage
that would allow us to simulate combat between creatures.

Some examples:
With temporary damage, creatures 1/2 and 1/3 can never kill one another.
With permanent damage, second creature will win after 2 rounds of combat.

With either temporary or permanent damage, two 2/2 creatures kill one another.

*/

#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
using namespace std;

struct Creature
{
    int attack, health;
    bool dead{false};       //Used dead flag to avoid modifying creatures health in TemporaryCardDamageGame
    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature> &creatures) : creatures(creatures) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        // todo
        hit(creatures[creature1], creatures[creature2]);

        if(creatures[creature1].dead && creatures[creature2].dead) {
            return - 1;
        } else if(!creatures[creature1].dead && !creatures[creature2].dead) {
            return - 1;
        } else {
            return creatures[creature1].dead ? creature2 : creature1;
        }
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override {
        
        if(attacker.attack >= other.health) {
            other.dead = true;
        }
        if(other.attack >= attacker.health) {
            attacker.dead = true;
        }
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature> &creatures) : CardGame(creatures) {}

    void hit(Creature &attacker, Creature &other) override
    {
        // todo
        attacker.health -= other.attack;
        other.health -= attacker.attack;

        attacker.dead = attacker.health <= 0;
        other.dead = other.health <= 0;
    }
};