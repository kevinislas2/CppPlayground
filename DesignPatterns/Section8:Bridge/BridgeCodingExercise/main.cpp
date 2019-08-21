/*
You are given an example of an inheritance hierarchy which results in Cartesian-product duplication

Please refactor this hierarchy, giving the base class Shape an initializer that takes a Renderer defined as:

    struct Renderer
    {
        virtual string what_to_render_as() const = 0;
    }

As well as VectorRenderer and RasterRenderer

The expectation is that each constructed object has a member called str() that returns its textual representation
For example:

Triangle(RasterRenderer()).str() // returns "Drawing Triangle as pixels"
*/
#include <iostream>

#include <string>
using namespace std;

struct Renderer
{
    virtual string what_to_render_as() const = 0;
};

struct Shape
{   
protected:
    string name;
    Renderer& renderer;
    virtual string str() const = 0;
public:
    Shape(Renderer& renderer): renderer{renderer} {}
};

struct Triangle : Shape
{ 
    // Copy and move constructor  
    Triangle(Renderer& renderer) : Shape{renderer}{
        name = "Triangle";
    }

    Triangle(Renderer&& renderer) : Shape{renderer}{
        name = "Triangle";
    }

    string str() const override {
        return "Drawing" + name + renderer.what_to_render_as();
    }
};

struct Square : Shape
{
    // Copy and move constructor  
    Square(Renderer& renderer) : Shape{renderer} {
        name = "Square";
    }

    Square(Renderer&& renderer) : Shape{renderer} {
        name = "Square";
    }

    string str() const override {
        return "Drawing " + name + renderer.what_to_render_as();
    }
};

// struct VectorSquare : Square
// {
//     string str() const
//     {
//         return "Drawing " + name + " as lines";
//     }
// };

// struct RasterSquare : Square
// {
//     string str() const
//     {
//         return "Drawing " + name + " as pixels";
//     }
// };

struct VectorRenderer : Renderer
{
    string what_to_render_as() const {
        return " as lines";
    }
};

struct RasterRenderer : Renderer
{
    string what_to_render_as() const {
        return " as pixels";
    }
};

int main()
{   
    // VectorRenderer vr{};
    // cout << Square{vr}.str() << '\n';

    cout << Square{RasterRenderer{}}.str() << '\n';
    return 0;
}
// imagine e.g. VectorTriangle/RasterTriangle etc. here