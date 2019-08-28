
#include <iostream>
#include <string>

using namespace std;

class Memento
{
    int balance;

public:
    Memento(int balance)
        : balance{balance}
    {}

    friend class BankAccount;
};

class BankAccount
{
    int balance{0};

public:
    BankAccount(int balance)
        : balance{balance}
    {}

    Memento deposit(int amount) {
        balance += amount;
        return Memento{balance};
    }

    void restore(const Memento& memento) {
        balance = memento.balance;
    }

    friend ostream& operator<<(ostream& os, const BankAccount &account) {
        os << "balance: " << account.balance;
        return os;
    }
};

int main()
{
    BankAccount ba{100};
    auto m1 = ba.deposit(50); // 150
    auto m2 = ba.deposit(25); //175

    cout << ba << '\n';

    ba.restore(m1);
    cout << "Back to m1 " << ba << '\n';

    ba.restore(m2);
    cout << "Back to m2 " << ba << '\n';
    
    return 0;
}