/*
Variants and std::visitor
g++ main.cpp -std=c++17 && ./a.out
*/

#include <iostream>
#include <string>
#include <variant>

using namespace std;

// Old CPP for a variant
// struct House{
//     union {
//         string house_name;
//         int house_number;
//     };
//     enum class Type {name, number} type;
// };

// Sort of a functor (with overloads)
struct AddressPrinter
{
    void operator()(const string& house_name) const {
        cout << "A house called " << house_name << '\n';
    }

    void operator()(const int house_number) const {
        cout << "House number " << house_number << '\n';
    }
};

int main()
{
    // For printing we need to build a visitor
    variant<string, int> house;
    house = 123;

    variant<string, int> house2;
    house2 = "Montefiore Castle";

    AddressPrinter ap;
    std::visit(ap, house);

    std::visit(ap, house2);

    // Solve with lambdas
    std::visit([](auto& arg)
    {
        using T = decay_t<decltype(arg)>;

        if constexpr (is_same_v<T, string>)
        {
            cout << "A house called " << arg << '\n';
        } else{
            cout << "House number " << arg << '\n';
        }
    }, house);

    return 0;
}