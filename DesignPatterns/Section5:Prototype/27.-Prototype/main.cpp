
/*
Prototype pattern
*/
#include <iostream>
#include <string>

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

int main()
{
    Contact john{"John Doe", new Address{"123 East Dr", "London", 123}};        //Obviusly leaks
    
    // For many Contacts we would need to replicate this calls
    // Contact jane{"Jane Smith", Address{"123 East Dr", "London", 103}};

    Contact jane {john}; //Deep copy
    jane.name = "Jane Smith";
    jane.address->suite = 103;

    cout << john << '\n';
    cout << jane << '\n';
}