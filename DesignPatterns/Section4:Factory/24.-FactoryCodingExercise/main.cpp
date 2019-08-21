/*
You are given a class called Person. The person has two fields; id and name
Implement a non-static PersonFactory that has a create_person() method that takes a person's name.

The id of the person should be set as a 0-based index of the object created. So the first person the factory makes should have id=0, 1.. so on
*/
#include <string>
#include <iostream>

using namespace std;

struct Person
{
  int id;
  string name;
};

class PersonFactory
{
public:
  Person create_person(const string& name)
  {
    static int id = 0;
    return {id++, name};
  }
};

int main()
{   
    PersonFactory pf{};
    for(size_t i = 0; i < 10; ++i) {
        Person p = pf.create_person("Name");
        cout << p.id << p.name << '\n';
    }

    PersonFactory pf2{};
    for(size_t i = 0; i < 10; ++i) {
        Person p = pf2.create_person("Name");
        cout << p.id << p.name << '\n';
    }
}