#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

using namespace std;

struct ChatRoom;

struct Person {
    string name;
    ChatRoom* room{nullptr};
    vector<string> chat_log;

    Person(const string& name);

    void say(const string& message) const;
    void private_message(const string& who, const string& message) const;
    void receive(const string& origin, const string& message);

    bool operator==(const Person& other) const;
    bool operator!=(const Person& other) const;
};

#endif