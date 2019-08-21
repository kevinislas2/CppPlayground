
/*
g++ main.cpp -pthread  && ./a.out 
*/
#include <iostream>
#include <string>

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>

using namespace std;
using namespace boost;

typedef uint32_t key;

struct User
{
    // string name;
    // string first_name, second_name;

    User(const string& first_name, const string& last_name)
    :   first_name{add(first_name)}, last_name{add(last_name)}
    {}

    // As of right now names are immutable
    const string& get_first_name() const {
        return names.left.find(first_name)->second;
    }

    const string& get_last_name() const {
        return names.left.find(last_name)->second;
    }

protected:
    key first_name, last_name;
    static bimap<key, string> names;
    static key seed;

    static key add(const string& s)
    {
        auto it = names.right.find(s);

        // string was not found in names bimap, add it
        if(it == names.right.end()) {
            key id = ++seed;
            names.insert({seed, s});
            return id;
        }

        return it->second;
    }

    friend ostream& operator<<(ostream &os, const User& user) {
    os << "first_name: " << user.get_first_name() << "(" << user.first_name << ")" << " last_name: " << user.get_last_name() << "(" << user.last_name << ")";
    return os;
}

};

key User::seed{0};
bimap<key, string> User::names{};

struct User2
{
    flyweight<string> first_name, last_name;

    User2(const string& first_name, const string& last_name)
        : first_name{first_name}, last_name{last_name}
        {}
};

int main(int argc, char* argv[])
{

    // User user1{"John Doe"};
    // User user2{"John Smith"};

    //Still repeats John internally
    // User user1{"John", "Doe"};
    // User user2{"John", "Smith"};

    // User user1{"John", "Smith"};
    // User user2{"Jane", "Smith"};

    // cout << user1 << '\n' << user2 << '\n';

    User2 first{"John", "Smith"};
    User2 second{"Jane", "Smith"};

    cout << first.first_name << '\n';
    
    cout << boolalpha;
    cout << (&first.first_name.get() == &second.first_name.get()) << '\n';
    cout << (&first.last_name.get() == &second.last_name.get()) << '\n';

    return 0;
}