/*

Visitor Coding Exercise

The unit tests for this assignment expect the inverse function names (visitor-accept)
from the original GoF... This file is equal to main.cpp but has the names reversed
so I can finish that assignment.

You are asked to implement a double-dispatch visitor called ExpressionPrinter
for printing different mathematical expressions. The range of expression covers
addition and multiplication - please put round brackets around addition but not
around multiplication! 
Also, please avoid any blank spaces in output.

Example:

Input: AdditionExpression{Literal{2}, Literal{3}} -- This is pseudocode, you cannot inline those references
Output (2+3)

Corresponding unit test:

Value v2{2};
Value v3{3};

AdditionExpression simple{v2, v3};

ExpressionPrinter ep;
ep.accept(simple);

ASSERT_EQ("(2+3)", ep.str());
*/
#include <iostream>

#include <string>
#include <sstream>
using namespace std;

struct Value;
struct AdditionExpression;
struct MultiplicationExpression;

struct ExpressionVisitor
{
    // accept methods here :)
    virtual void accept(Value& value) = 0;
    virtual void accept(AdditionExpression& additionExpression) = 0;
    virtual void accept(MultiplicationExpression& multiplicationExpression) = 0;
};

struct Expression
{
    virtual void visit(ExpressionVisitor& ev) = 0;
    virtual ~Expression() = default;
};

struct Value : Expression
{
    int value;

    Value(int value) : value(value) {}

    void visit(ExpressionVisitor& ev) {
        ev.accept(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression &lhs, &rhs;

    AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor& ev) {
        ev.accept(*this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs, &rhs;

    MultiplicationExpression(Expression &lhs, Expression &rhs)
    : lhs(lhs), rhs(rhs) {}

    void visit(ExpressionVisitor& ev) {
        ev.accept(*this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;
    // accept methods here :)
    void accept(Value& value) {
        oss << value.value;
    };

    void accept(AdditionExpression& additionExpression) {

        oss << '(';
        additionExpression.lhs.visit(*this);
        oss << '+';
        additionExpression.rhs.visit(*this);
        oss << ')';
    };

    void accept(MultiplicationExpression& multiplicationExpression) {
        
        multiplicationExpression.lhs.visit(*this);
        oss << '*';
        multiplicationExpression.rhs.visit(*this);

    }

    string str() const { 
        return oss.str();
    }
};

int main() {
    Value v2{2};
    Value v3{3};

    // AdditionExpression simple{v2, v3};
    MultiplicationExpression simple{v2, v3};

    ExpressionPrinter ep;
    ep.accept(simple);

    cout << ep.str() << '\n';
    return 0;
}