
#include <iostream>
#include <string>

using namespace std;

#include "observer.h"

class Person // Observable
{
    int age;

public:
    int get_age() const { return age; }
    void set_age(int age) { Person::age = age; } 
};

// Observer & observable

struct ConsolePersonObserver
    : public Observer<Person>
{
private:
    void field_changed(Person& source, const string& field_name) override {
        cout << "Person's " << field_name << "has changed to ";
        if(field_name == "age") {
            cout << source.get_age();
        }
        cout << '\n';
    }
};

int main()
{   

    return 0;
}