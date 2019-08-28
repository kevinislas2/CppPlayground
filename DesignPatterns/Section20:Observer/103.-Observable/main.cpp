
#include <iostream>
#include <string>

using namespace std;

#include "observer.h"
#include "observable.h"

class Person : public Observable<Person> // Observable
{
    int age;

public:
    int get_age() const {
        return age;
    }
    void set_age(int age) {

        if(this->age != age) {
            this->age = age;
            notify(*this, "age");
        }
        
    }

    Person(int age)
        : age{age}
    {
    }
};

// Observer & observable

struct ConsolePersonObserver
    : public Observer<Person>
{
private:
    void field_changed(Person& source, const string& field_name) override {
        cout << "Person's " << field_name << " has changed to ";
        if(field_name == "age") {
            cout << source.get_age();
        }
        cout << '\n';
    }
};

int main()
{   
    Person person{10};
    ConsolePersonObserver cpo{};
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);

    person.set_age(20);

    return 0;
}