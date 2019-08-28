/*
Handling events in a centralized manner

Mediator design pattern coupled with the observer design pattern
*/
#include <iostream>
#include <string>

#include <boost/signals2.hpp>

using namespace std;
using namespace boost;

struct EventData
{
    virtual void print() const = 0;
};

struct PlayerScoredData : EventData
{
    string player_name;
    int goals_scored_so_far;

    PlayerScoredData(const string& player_name, int goals_scored_so_far)
        : player_name{player_name}, goals_scored_so_far{goals_scored_so_far}
    {}

    void print() const override
    {
        cout << player_name << " has scored! (their " << goals_scored_so_far << " goal)\n";
    }
};

// Game is the event broker
struct Game
{
    signals2::signal<void(EventData*)> events;
};

struct Player
{
    string name;
    int goals_scored{0};
    Game& game;

    Player(const string& name, Game& game)
        : name{name}, game{game}
    {}

    void score()
    {
        ++goals_scored;
        PlayerScoredData ps{name, goals_scored};
        game.events(&ps);                           //Post the event
    }
};

struct Coach
{
    Game& game;
    signals2::connection c;

    Coach(Game& game)
        : game{game}
    {   
        //Store connection in member variable so we can disconnect on destructor
        c = game.events.connect([](EventData* e)
        {
            // We might have polymorphic behaviour, so we cast and check if the event is of type PlayerScoredData
            PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);

            if(ps && ps->goals_scored_so_far < 3)
            {
                cout << "Coach says: well done, " << ps->player_name << "!\n";
            }
        });
    }

    ~Coach() {
        //Disconnect on destructor
        //It would probably make more sense to store the connection in the Game class
        //This way the connection would be bound between a player and a game by the coach
        c.disconnect();
    }
};

int main()
{
    Game game;
    Player player{"Sam", game};
    Coach coach{game};

    player.score();
    player.score();
    player.score();
}