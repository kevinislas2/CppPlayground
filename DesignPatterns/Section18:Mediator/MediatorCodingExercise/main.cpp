/*
Mediator Coding Exercise:

Our system has a number of instances of Participant classes.
Each participant has a value integer, initially zero.

A participant can say() a particular value, which is broadcast to all other participants.
At this point in time, every other participant is obliged to increase their value by the value being broadcast.

Example:

* Two participants start with values 0 and 0 respectively.
* Participant 1 broadcasts the value 3. We now have Participant 1 value = 0, Participant 2 value = 3.
* Participant 2 broadcasts the value 2. We now have Participant 2 value = 2, Participant 2 value = 3.

*/

#include <vector>
#include <iostream>

using namespace std;

struct IParticipant
{
    virtual void say(int value) = 0;
    virtual void addValue(int v) = 0;
};

struct Mediator {

    vector<IParticipant*> participants;

    void say(IParticipant* participant, int value) {

        for(IParticipant* p : participants) {

            if(p != participant) {
                p->addValue(value);
            }
        }
    }

};

struct Participant : IParticipant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void say(int value) override
    {
        // todo (solved)
        mediator.say(this, value);
    }

    void addValue(int v) override
    {
        value += v;
    }
};

int main()
{
    Mediator m{};
    Participant p1{m};
    Participant p2{m};

    cout << "P1: " << p1.value << " P2: " << p2.value << '\n';

    p1.say(3);

    cout << "P1: " << p1.value << " P2: " << p2.value << '\n';

    p2.say(2);

    cout << "P1: " << p1.value << " P2: " << p2.value << '\n';

    return 0;
}