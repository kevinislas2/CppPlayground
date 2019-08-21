/*
Proxy Coding Exercise:

You are given the Person class and asked to write a ResponsiblePerson wrapper/proxy that does the following:

Allows person to drink unless they are younger than 18 (in that case returns "too young")
Allows the person to drive unless they are younger than 16 (otherwise "too young")
In case of driving while drunk, returns "dead"

The interface of ResponsiblePerson has to match that of Person, except for the constructor
which takes an underlying Person object
*/

#include <string>
#include <iostream>

using namespace std;

class Person
{
  friend class ResponsiblePerson;
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:
    ResponsiblePerson(const Person &person) : person(person) {}

    int get_age() const {
        return person.get_age();
    }

    int set_age(int age) {
        person.set_age(age);
    }

    string drink() const {
        if(get_age() < 18) {
            return "too young";
        }
        return person.drink();
    }

    string drive() const {
        if(get_age() < 16) {
            return "too young";
        }
        return person.drive();
    }

    string drink_and_drive() const {
        return "dead";
    }

private:
    Person person;
};

int main() {

    Person person{10};
    Person person2{20};

    ResponsiblePerson rPerson1{person};
    ResponsiblePerson rPerson2{person2};

    cout << rPerson1.drink() << '\n'
        << rPerson1.drive() << '\n'
        << rPerson1.drink_and_drive() << '\n';

    cout << rPerson2.drink() << '\n'
    << rPerson2.drive() << '\n'
    << rPerson2.drink_and_drive() << '\n';

}