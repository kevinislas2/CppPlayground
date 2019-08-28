#include <algorithm>

#include "chatroom.hpp"
#include "person.hpp"

void ChatRoom::broadcast(const string& origin, const string& message)
{
    for(auto p : people) {
        if(p->name != origin) {
            p->receive(origin, message);
        }
    }
}

void ChatRoom::join(Person* p)
{
    string join_msg = p->name + " joins the chat";

    broadcast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

void ChatRoom::message(const string& origin,
                        const string& who,
                        const string& message)
{
    // Can be optimized by storing people in a map instead of a vector
    auto target = std::find_if(
        begin(people),
        end(people),
        [&](const Person *p) {
            return p->name == who;
        }
    );

    if (target != end(people))
    {
        (*target)->receive(origin, message);
    }
}