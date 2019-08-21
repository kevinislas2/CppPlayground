#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ContainsIntegers {
	virtual int sum() const = 0;
};

struct SingleValue: ContainsIntegers
{
  int value{ 0 };

  SingleValue() = default;

  explicit SingleValue(const int value)
    : value{value}
  {
  }

  int sum() const override {
    return value;
  }
  
};

struct ManyValues : vector<int>, ContainsIntegers
{
  void add(const int value)
  {
    push_back(value);
  }

  int sum() const override {
    int result = 0;
    for(auto i : *this) {
      result += i;
    }
    return result;
  }
};

int sum(const vector<ContainsIntegers*> items);