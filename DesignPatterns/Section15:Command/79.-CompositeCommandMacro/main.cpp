
#include <iostream>
#include <vector>
#include <initializer_list>

using namespace std;

struct BankAccount
{
    int balance{0};
    int overdraft_limit{-500};

    void deposit(int amount)
    {
        balance += amount;
        cout << "deposited " << amount << ", balance is now "
            << balance << '\n';
    }

    bool withdraw(int amount)
    {
        if(balance - amount >= overdraft_limit)
        {
            balance -= amount;
            cout << "withdrew " << amount
                << ", balance is now " << balance << '\n';
            return true;
        }
        return false;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& account) {
        os << "balance: " << account.balance;
        return os;
    }
};

struct Command
{
    bool succeeded;
    virtual void call() = 0;
    virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
    BankAccount& account;
    enum Action {deposit, withdraw} action;
    int amount;

    BankAccountCommand(BankAccount& account, Action action, int amount)
        : account{account}, action{action}, amount{amount}
        {
            succeeded = false;
        }

    void call() override {
        switch (action)
        {
        case deposit:
            account.deposit(amount);
            succeeded = true;
            break;

        case withdraw:
            succeeded = account.withdraw(amount);
            break;
        }
    }
    void undo() override {

        //This checks if the operation succedeed
        if(!succeeded) return;
        //Assumes that they are symmetric, they arent
        //If withdraw doesnt succeed we will add money to the account
        switch (action)
        {
        case deposit:
            account.withdraw(amount);
            break;
        
        case withdraw:
            account.deposit(amount);
            break;
        }
    }
};

// Naive implementation
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command // Inheriting from vector is tricky because it doesnt have virtual destructor
{
    CompositeBankAccountCommand(const initializer_list<BankAccountCommand>& items)
        : vector{items}
        {}
    
    void call() override {
        for(auto& cmd : *this) {
            cmd.call();
        }
    }

    void undo() override {
        for(auto it = rbegin(); it != rend(); ++it) {
            it->undo();
        }
    }
};

//Better implementation
struct DependantCompositeCommand : CompositeBankAccountCommand
{
    DependantCompositeCommand(const initializer_list<BankAccountCommand>& items)
        : CompositeBankAccountCommand(items)
    {}

    void call() override {

        // Store pointer to each successful command
        vector<BankAccountCommand*> successfulCommands{};

        bool ok = true;
        for(auto& cmd : *this)
        {
            // We could further improve this and store each successful command, 
            // Then if at some point one command fails, rollback every previous command
            if(ok)
            {
                cmd.call();
                ok = cmd.succeeded;

                successfulCommands.push_back(&cmd); // Store command
            } else {
                cmd.succeeded = false;
            }
        }

        //Something failed, rollback each successful command
        if(!ok) {
            for(BankAccountCommand* cmd : successfulCommands) {
                cmd->undo();
            }
        }

        // I believe DB implementations actually use this kind of logic for batch operations;
        // However, in a multithreaded environment this batch of operations would also be bound to a lock
        // To avoid race conditions
        
    }
};

struct MoneyTransferCommand : DependantCompositeCommand
{
    MoneyTransferCommand(BankAccount& from, BankAccount& to, int amount)
        : DependantCompositeCommand(
            {
                BankAccountCommand{from, BankAccountCommand::withdraw, amount},
                BankAccountCommand{from, BankAccountCommand::deposit, amount}       //Deposit should fail if withdraw fails
            })
        {}
};

int main() 
{
    BankAccount ba;
    BankAccount ba2;

    ba.deposit(100);
    
    MoneyTransferCommand cmd{ba, ba2, 5000};
    cmd.call();

    cout << ba << '\n';
    cout << ba2 << '\n';

    cmd.undo();

    cout << ba << '\n';
    cout << ba2 << '\n';

    return 0;
}