
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template<typename Visitable>
struct Visitor
{
    virtual void visit(Visitable& obj) = 0;
};

struct VisitorBase
{   
    //We need to have a vtable so we need at least one method
    virtual ~VisitorBase() = default;
};

struct Expression
{
    virtual ~Expression() = default;

    virtual void accept(VisitorBase& obj)           // <- Visitor<T>
    {
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&obj)) {     // We make sure that the obj can actually visit an Expression through Visitor<Expression>
            ev->visit(*this);
        }
    }
};

struct DoubleExpression : Expression
{
    double value;
    DoubleExpression(double value) : value{value} {}

    virtual void accept(VisitorBase& obj)           // <- Visitor<T>
    {
        using DEV = Visitor<DoubleExpression>;
        if(auto ev = dynamic_cast<DEV*>(&obj)) {     // We make sure that the obj can actually visit an Expression through Visitor<DoubleExpression>
            ev->visit(*this);
        }
    }
};

struct AdditionExpression : Expression
{
    Expression *left, *right;

    AdditionExpression(Expression* left, Expression* right) 
        : left{left}, right{right}
    {}

    ~AdditionExpression() {
        delete left;
        delete right;
    }

    virtual void accept(VisitorBase& obj)           // <- Visitor<T>
    {
        using AEV = Visitor<AdditionExpression>;
        if(auto ev = dynamic_cast<AEV*>(&obj)) {     // We make sure that the obj can actually visit an Expression through Visitor<AdditionExpression>
            ev->visit(*this);
        }
    }
};

//VisitorBase only has a virtual destructor, but inheriting allows us to be compatible with every accept function
//This allows us to have more freedom in class hierarchies and provides certain safety measures
//If the VisitorBase does not provide a visit<T> overload it doesnt pass the dynamic cast in accept and nothing happens
struct ExpressionPrinter :  VisitorBase,
                           Visitor<DoubleExpression>,       //To be able to access Visitor<DoubleExpression>
                            Visitor<AdditionExpression>     //To be able to access Visitor<AdditionExpression>
{
    void visit(DoubleExpression &obj) override
    {
        oss << obj.value;
    }

    void visit(AdditionExpression &obj) override 
    {
        oss << '(';
        obj.left->accept(*this);
        oss << '+';
        obj.right->accept(*this);
        oss << ')';
    }

    string str() const {return oss.str(); } 
private:
    ostringstream oss;
};

int main()
{
    auto e = new AdditionExpression {
        new DoubleExpression{1},
        new AdditionExpression{
            new DoubleExpression{2},
            new DoubleExpression{3}
        }
    };

    ExpressionPrinter ep;
    ep.visit(*e);

    cout << ep.str() << '\n';

    return 0;
}