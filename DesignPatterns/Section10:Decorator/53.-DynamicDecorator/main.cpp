
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Shape
{
    virtual string str() const = 0;
};

struct Circle : Shape
{
    float radius;

    Circle() {}
    Circle(float radius) : radius{radius} {}

    void resize(float factor) {
        radius *= factor;
    }

    string str() const override {
        ostringstream oss;
        oss << "A circle of radius " << radius;
        return oss.str();
    }
};

struct Square : Shape
{
    float side;
    
    Square(float side) : side{side} {}
    Square() {}

    string str() const override {
        ostringstream oss;
        oss << "A square with side " << side;
        return oss.str();
    }
};

// Dynamic Decorator
struct ColoredShape: Shape
{
    Shape& shape;
    string color;

    ColoredShape(Shape& shape, const string &color)
        : shape{shape}, color{color} 
        {}

    string str() const override {
        ostringstream oss;

        oss << shape.str() << " has the color " << color;
        return oss.str();
    }
};

// Dynamic Decorator 2
struct TransparentShape : Shape
{
    Shape& shape;
    uint8_t transparency;

    TransparentShape(Shape& shape, uint8_t transparency)
        : shape{shape}, transparency{transparency}
        {}

    string str() const override {
        ostringstream oss;

        oss << shape.str() << " has " << static_cast<float>(transparency) / 255.f * 100.f
            << "% transparency";
        return oss.str();
    }
};

int main()
{

    Circle circle{5};

    ColoredShape red_circle{circle, "red"};

    cout << circle.str() << '\n' << red_circle.str() << '\n';

    TransparentShape my_circle{red_circle, 51};
    cout << my_circle.str() << '\n';


    return 0;
}