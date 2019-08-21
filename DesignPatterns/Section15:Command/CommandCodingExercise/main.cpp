/*
Comand Coding Exercise:

Implement the Account::process() function to process diferent account commands. The rules are obvious:

success indicates whether the operation was successful
You can only withdraw money if you have enough in your account

*/

#include <iostream>

using std::cout;

struct Command
{
  enum Action { deposit, withdraw } action;
  int amount{0};
  bool success{false};
};

struct Account
{
  int balance{0};

  void process(Command& cmd)
  {
    // todo
    switch (cmd.action){
        case Command::deposit:
            balance += cmd.amount;
            cmd.success = true;
            break;

        case Command::withdraw:
            if(balance >= cmd.amount) {
                balance -= cmd.amount;
                cmd.success = true;
            } else {
                cmd.success = false;
            }
            break;
    }
  }
};

int main()
{

    Account ac;

    Command add{Command::deposit, 100};
    ac.process(add);

    cout << ac.balance << '\n';

    Command withdraw{Command::withdraw, 100};
    ac.process(withdraw);

    cout << ac.balance  << '\n';

    ac.process(withdraw);

    cout << ac.balance  << '\n';

    return 0;
}