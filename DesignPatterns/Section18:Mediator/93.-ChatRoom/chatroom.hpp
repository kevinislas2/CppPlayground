#ifndef CHATROOM_H
#define CHATROOM_H

#include <vector>
#include <string>

struct Person;

using namespace std;

struct ChatRoom {
    vector<Person*> people;

    void broadcast(const string& origin, const string& message);

    void join(Person* p);

    void message(const string& origin, 
                const string& who, 
                const string& message);
};

#endif