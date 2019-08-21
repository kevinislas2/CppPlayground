
#include <iostream>
#include <string>

using namespace std;

template<typename T>
struct Property
{
    T value;

    Property(T value)
    {
        *this = value;
    }

    operator T()
    {
        return value;
    }

    // Value semantics
    T operator=(T new_value)
    {
        cout << "Assignment!\n";
        return value = new_value;
    }
};

struct Creature
{
    Property<int> strength{10};
    Property<int> agility{5};
};


int main()
{
    Creature c;
    c.strength = 11;
    int x = c.agility;
    return 0;
}