/*
State Machine Coding Exercise

A combination lock is a lock that opens after the right digits have been entered.
A lock is preprogrammed with a combination (e.g., 12345) and the user is expected
to enter this combination to unlock the lock.

The lock has a status field that indicates the state of the lock. The rules are:

* If the lock has just been locked (or at startup), the status is LOCKED.

* If a digit has been entered, that digit is shown on the screen. As the user enters
    more digits, they are added to Status.

* If the user has entered the correct sequence of digits, the lock status changes to OPEN

* If the user enters an incorrect sequence of digits, the lock status changes to ERROR

Please implement the CombinationLock class to enable this behaviour. Be sure to test
both correct and incorrect inputs.

Here is an example unit test for the lock:

CombinationLock cl({1, 2, 3});
ASSERT_EQ("LOCKED", cl.status);
cl.enter_digit(1);
ASSERT_EQ("1", cl.status);
cl.enter_digit(2);
ASSERT_EQ("12", cl.status);
cl.enter_digit(3);
ASSERT_EQ("OPEN", cl.status);

*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <cassert>

using namespace std;

class CombinationLock
{
    vector<int> combination;
    vector<int> attemptedCombination;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination), status{"LOCKED"} {
      
    }

    void enter_digit(int digit)
    {
        // TODO
        stringstream ss;
        if(attemptedCombination.size() != 0) {
            ss << status;
        }

        attemptedCombination.push_back(digit);

        if(attemptedCombination.size() < combination.size()) {

            ss << digit;
            status = ss.str();
        } else {
            
            status = "OPEN";
            for(size_t i = 0; i < attemptedCombination.size(); ++i) {
                if(attemptedCombination[i] != combination[i]) {
                    status = "ERROR";
                    break;
                }
            }
        }
    }
};

int main() {
    CombinationLock cl({1, 2, 3});

    assert(cl.status == "LOCKED");
    cl.enter_digit(1);
    assert(cl.status == "1");
    cl.enter_digit(2);
    assert(cl.status == "12");
    cl.enter_digit(3);
    assert(cl.status == "OPEN");
}