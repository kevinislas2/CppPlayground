/*
Singleton Coding Exercise:

You are given the function SingletonTester::is_singleton() defined below. 
This function takes a factory, and needs to return true or false depending
on wherher that factory produces singletons.
*/

#include <functional>
using namespace std;

struct SingletonTester
{
  template <typename T>
  bool is_singleton(function<T*()> factory) // Factory returns a pointer to T
  {
    return factory() == factory(); // check if two calls to factory yield the same pointer value
  }
};
int main() {

}