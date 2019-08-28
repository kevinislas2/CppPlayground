/*
Intrusive visitor (breaking open/closed principle)
*/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Expression
{
    virtual ~Expression() = default;

    virtual void print(ostringstream& oss) = 0;     // Intrusive visitor, must be implemented in the hierarchy
};

// Expressions are like 1+2+3

struct DoubleExpression : Expression {
    double value;

    DoubleExpression(double value) : value{value} {}

    void print(ostringstream& oss) override {
        oss << value;
    }
};

struct AdditionExpression : Expression
{
/* We may have expression of expressions

        1 + 2 + 3
          +
         / \
        1   +
           / \
          2   3
*/

    Expression *left, *right;

    AdditionExpression(Expression *left, Expression *right)
        : left {left} , right{right}
    {}

    ~AdditionExpression()
    {
        delete left;
        delete right;
    }

    void print(ostringstream& oss) override {
        oss << '(';
        left->print(oss);
        oss << '+';
        right->print(oss);
        oss << ')';
    }
};

int main()
{
    auto e = new AdditionExpression{
        new DoubleExpression{1},
        new AdditionExpression
            {
                new DoubleExpression{2},
                new DoubleExpression{3}
            }
    };

    // We expect to print something like (1+(2+3))

    ostringstream oss;
    e->print(oss);
    cout << oss.str() << '\n';

    delete e;
    return 0;
}
