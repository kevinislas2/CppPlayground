/*
Visitor using reflection mechanisms (dynamic casts)
*/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Expression
{
    virtual ~Expression() = default;
};

// Expressions are like 1+2+3

struct DoubleExpression : Expression {
    double value;

    DoubleExpression(double value) : value{value} {}

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
};

// struct ExpressionPrinter
// {
//     void print(DoubleExpression *de, ostringstream& oss) const {
//         oss << de->value;
//     }

//     void print(AdditionExpression *de, ostringstream& oss) const {
//         oss << '(';
//         //print(ae->left, oss);                 // No overload of print for Addition (problem with statically typed compiled languages)
//                                                 // No way to determine at compile time what kind of expression ae is
//                                                 // (so)

//     }
// };

struct ExpressionPrinter
{
    ostringstream oss;
    string str() const { return oss.str();}

    void print(Expression* e) {

        // How can we determine the type? Simple way using dynamic casts
        // Downsides are run-time cost, does not scale very well
        // What if we have 50 expression types?
        if(auto de = dynamic_cast<DoubleExpression*>(e)) {
            oss << de->value;
        } else if(auto ae = dynamic_cast<AdditionExpression*>(e)) {
            oss << '(';
            print(ae->left);
            oss << '+';
            print(ae->right);
            oss << ')';
        }
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

    ExpressionPrinter ep;
    ep.print(e);
    cout << ep.str() << '\n';
    delete e;
    return 0;
}
