/*

Visitor Coding Exercise

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
    // visit methods here :)
    virtual void visit(Value& value) = 0;
    virtual void visit(AdditionExpression& additionExpression) = 0;
    virtual void visit(MultiplicationExpression& multiplicationExpression) = 0;
};

struct Expression
{
    virtual void accept(ExpressionVisitor& ev) = 0;
    virtual ~Expression() = default;
};

struct Value : Expression
{
    int value;

    Value(int value) : value(value) {}

    void accept(ExpressionVisitor& ev) {
        ev.visit(*this);
    }
};

struct AdditionExpression : Expression
{
    Expression &lhs, &rhs;

    AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}

    void accept(ExpressionVisitor& ev) {
        ev.visit(*this);
    }
};

struct MultiplicationExpression : Expression
{
    Expression &lhs, &rhs;

    MultiplicationExpression(Expression &lhs, Expression &rhs)
    : lhs(lhs), rhs(rhs) {}

    void accept(ExpressionVisitor& ev) {
        ev.visit(*this);
    }
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss;
    // visit methods here :)
    void visit(Value& value) {
        oss << value.value;
    };

    void visit(AdditionExpression& additionExpression) {
        oss << '(';
        additionExpression.lhs.accept(*this);
        oss << '+';
        additionExpression.rhs.accept(*this);
        oss << ')';
    };

    void visit(MultiplicationExpression& multiplicationExpression) {

        multiplicationExpression.lhs.accept(*this);
        oss << '*';
        multiplicationExpression.rhs.accept(*this);

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
    ep.visit(simple);

    cout << ep.str() << '\n';
    return 0;
}