
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

int main()
{
    Person p{10};
    ConsolePersonObserver cpo{};

    p.subscribe(cpo);

    p.set_age(15);
    p.set_age(16);
    return 0;
}