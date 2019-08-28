
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

class Memento
{
    int balance;

public:
    Memento(int balance)
        : balance{balance}
    {}

    friend class BankAccount;
    friend class BankAccount2;
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

class BankAccount2
{
    int balance{0};

    vector<shared_ptr<Memento>> changes;
    int current;

public:

    BankAccount2(int balance)
        : balance{balance}
    {
        changes.emplace_back(make_shared<Memento>(balance));
        current = 0;
    }

    shared_ptr<Memento> deposit(int amount) {
        balance += amount;
        auto m = make_shared<Memento>(balance);
        changes.push_back(m);
        ++current;
        return m;
    }

    void restore(const shared_ptr<Memento>& memento) {
        if(memento)
        {
            balance = memento->balance;
            changes.push_back(memento);
            current = changes.size() - 1;
        }
    }

    shared_ptr<Memento> undo()
    {
        if(current > 0) {
            --current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
        return {};
    }

    shared_ptr<Memento> redo()
    {
        if(current + 1 < changes.size())
        {
            ++current;
            auto m = changes[current];
            balance = m->balance;
            return m;
        }
    }

    friend ostream& operator<<(ostream& os, const BankAccount2& account) {
        os << "Balance: " << account.balance;
        return os;
    } 
};

int main()
{
    BankAccount2 ba{100};
    ba.deposit(50);
    ba.deposit(25); // 175
    cout << ba << '\n';

    ba.undo();
    cout << "Undo 1 " << ba << '\n';

    ba.undo();
    cout << "Undo 2 " << ba << '\n';

    ba.redo();
    cout << "Redo " << ba << '\n';
    return 0;
}