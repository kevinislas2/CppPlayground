
#include <iostream>
#include <string>

using namespace std;

#include <boost/signals2.hpp>

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

template<typename T>
struct Observable2
{
    boost::signals2::signal<void(T&, const string&)> field_changed;
};

class Person2 : public Observable2<Person2>
{
    int age;
public:
    int get_age() const {
        return age;
    }

    void set_age(int age) {

        if(age != this->age) {
            this->age = age;
            field_changed(*this, "age");
        }
    }
};

int main()
{
    Person2 p2{};

    auto connection = p2.field_changed.connect(
        [](Person2& p, const string& field_name) {
            cout << field_name << " has changed\n";
        }
    );

    p2.set_age(20);

    connection.disconnect();

    p2.set_age(30);
    
    return 0;
}