
/*
Prototype factory
*/
#include <iostream>
#include <string>
#include <memory>


using namespace std;

struct Address
{
    string street, city;
    int suite;

    Address(const string& street, const string& city, int suite) 
        : street{street}, city{city}, suite{suite} {}

    friend ostream &operator <<(ostream& os, const Address &address) {
        os << "street: " << address.street << " city: " << address.city
            << " suite: " << address.suite;
        return os;
    }

    Address(const Address& other)
    : street{other.street}, city{other.city}, suite{other.suite}
    {
    }
};

struct Contact
{
    string name;

    // Works if we store by value instead of reference
    // Address address;

    // This will shallow copy the pointer
    Address* address;

    // Contact(const string& name, const Address address)
    //     : name{name}, address{address} {}
    Contact(const string& name, Address* address)
        : name{name}, address{address} {}

    friend ostream &operator <<(ostream& os, const Contact &contact) {
        os << "name: " << contact.name << " address: " << *contact.address;
        
        return os;
    }

    // Define a copy constructor
    Contact(const Contact& other) 
        : name {other.name},
        address {new Address { *other.address}}
    {
    }

    ~Contact() {
        delete address;
    }
};

struct EmployeeFactory
{

    static unique_ptr<Contact> new_main_office_employee
        (const string& name, const int suite)
        {
            static Contact p{"", new Address{"123 East Dr", "London", 0}};
            return new_employee(name, suite, p);
        }
private:
    static unique_ptr<Contact> new_employee(const string& name, const int suite, const Contact& prototype)
    {
        auto result = make_unique<Contact>(prototype);
        result->name = name;
        result->address->suite = suite;
        return result;
    }
};

Contact main_contact{"", new Address{"123 East Dr", "London", 0}};

int main()
{
    auto john = EmployeeFactory::new_main_office_employee("John", 123);

    cout << *john << '\n';
}