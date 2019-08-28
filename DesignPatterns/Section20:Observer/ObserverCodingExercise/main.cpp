/*
Observer Coding Exercise

Imagine a game where one or more rats can attack a player. Each individual rat has an attack value of 1. 
However, rats attack as a swarm, so each rat's attack value is equal to the number of rats in play.

Given that a rats enters play through the constructor and leaves play (dies) via its destructor, please
implement the Game and Rat classes so that, at any point in the game, the attack value of a rat is always
consistent.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Game;

struct IRat{

    virtual void subscribe(Game& game) = 0;
    virtual void unsuscribe(Game& game) = 0;
    virtual void setAttack(int attack) = 0;
    virtual int getAttack() const = 0;
};

struct Game
{
    // todo
    enum class eventType {Add, Remove};

    std::vector<IRat*> rats = {};

    Game game() {}

    void notify(IRat* rat, eventType event) {

        switch (event)
        {
        case eventType::Add:
            rats.push_back(rat);

            updateRatsAttack();

            break;
        
        case eventType::Remove:

            rats.erase(
                remove(rats.begin(), rats.end(), rat),
                rats.end()
            );

            updateRatsAttack();

            break;
        }
    }

    void updateRatsAttack() {
        for(IRat* rat : rats) {
            rat->setAttack(rats.size());
        }
    }

};


struct Rat : IRat
{
    Game& game;
    int attack{1};

    Rat(Game &game) : game(game)
    {
      // todo, obviously
      subscribe(game);
    }

    ~Rat() 
    { 
        // rat dies here!
        unsuscribe(game);
    }

    void subscribe(Game& game) override {
        game.notify(this, Game::eventType::Add);
    }

    void unsuscribe(Game& game) override {
        game.notify(this, Game::eventType::Remove);
    }

    void setAttack(int attack) override {
        this->attack = attack;
    }

    int getAttack() const override {
        return attack;
    }

};

int main() {

    Game game;
    Rat* r1 = new Rat(game);
    Rat* r2 = new Rat(game);
    Rat* r3 = new Rat(game);

    for(auto rat : game.rats) {
        cout << rat->getAttack() << '\n';
    }

    delete r2;

    for(auto rat : game.rats) {
        cout << rat->getAttack() << '\n';
    }
}