/*
Memento Coding Exercise

A TokenMachine is in charge of keeping Tokens. Each Token is a reference type with a single numerical value.
The machine supports adding tokens and, when it does, it returns a memento representing the state of that 
system at a given time.

You are asked to fill in the gaps and implement the memento design pattern for this scenario.
Pay close attention to the situation where a token is fed in as a smart pointer and its value
is subsequently changed on that pointer - you still need to return the correct system snapshot!
*/

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

struct Token
{
  int value;

  Token(int value) : value(value) {}
};

struct Memento
{
  vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
  vector<shared_ptr<Token>> tokens;

  Memento add_token(int value)
  {
    return add_token(make_shared<Token>(value));
  }

  // adds the token to the set of tokens and returns the
  // snapshot of the entire system
  Memento add_token(const shared_ptr<Token>& token)
  {
    // todo
    tokens.push_back(make_shared<Token>(Token{token->value}));      //This is ok, we construct a new Token and push it
    // tokens.push_back(token);                                     //This would be wrong, a token can later be modified
    return Memento{tokens};
  }

  // reverts the system to a state represented by the token
  void revert(const Memento& m)
  {
      // todo
      tokens = m.tokens;
  }
};

int main()
{
    TokenMachine tm{};
    tm.add_token(1);
    Memento memento = tm.add_token(2);

    auto t = make_shared<Token>(Token{3});
    tm.add_token(t);
    t->value = 5;

    for(auto t : tm.tokens) {
        cout << "T - " << t->value << '\n';
    }

    tm.revert(memento);

    for(auto t : tm.tokens) {
        cout << "T - " << t->value << '\n';
    }
    return 0;
}