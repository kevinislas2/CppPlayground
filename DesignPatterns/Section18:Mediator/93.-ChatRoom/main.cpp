/*
Chat room example
*/
#include <iostream>
#include <string>

#include "person.hpp"
#include "chatroom.hpp"

using namespace std;

int main()
{
    ChatRoom room{};

    Person john{"John"};
    Person jane{"Jane"};

    room.join(&john);
    room.join(&jane);

    john.say("Hi room");
    jane.say("Oh, hey John");

    Person simon{"Simon"};
    room.join(&simon);

    simon.say("Hi everyone");

    jane.private_message("Simon", "glad you found us");
    return 0;
}