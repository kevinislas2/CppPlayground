//clang++ -std=c++17 main.cpp && ./a.out

#include <iostream>
#include <string>

using namespace std;

#include "observer.h"
// #include "observable.h"
#include "saferObservable.h"

class Person : public SaferObservable<Person> // Observable
{
    int age;

public:
    int get_age() const {
        return age;
    }
    void set_age(int age) {

        if(this->age == age) return;

        auto old_can_vote = get_can_vote();
        this->age = age;
        notify(*this, "age");

        // Dependencies on notifications become extremely tricky
        if(old_can_vote != get_can_vote()) {
            notify(*this, "can_vote");
        }
    }
    bool get_can_vote() const {
        return age >= 16;
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

        //This approach does not scale very well
        if(field_name == "age") {
            cout << source.get_age();
        } else if(field_name == "can_vote") {
            cout << boolalpha << source.get_can_vote();
        }
        cout << '\n';
    }
};

struct TrafficAdministration : Observer<Person>
{
    void field_changed(Person& source, const std::string& field_name) override
    {
        if(field_name == "age")
        {
            if(source.get_age() < 17) {
                cout << "Whoa there, you're not old enough to drive!\n";
            } else {
                cout << "Oh, ok, we no longer care!\n";
                source.unsubscribe(*this);                  // Reentrancy problem, calling unsuscribe inside notify using same mutex
            }
        }
    }
};

int main()
{
    Person p{10};
    TrafficAdministration ta;
    p.subscribe(ta);

    p.set_age(15);
    p.set_age(16);

    // Should throw an exception (device busy), it doesnt
    try {
        p.set_age(17);
    } catch (const std::exception& e) {
        cout << e.what() << '\n';
    }

    return 0;
}