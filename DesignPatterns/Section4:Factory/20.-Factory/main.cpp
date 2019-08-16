/*
Example of where a Factory
Move code specialized in construction of an object into a separate component
*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

enum class PointType
{
    cartesian,
    polar
};

class Point
{
    // friend class PointFactory;                  // Unfortunately violates Open-Closed principle (OCP) because we modified Point
    
    //solved by making constructor public
    public:
    Point(float x, float y) : x{x}, y{y} {}

    float x, y;

    friend ostream &operator<<(ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }
};

struct PointFactory
{
    // May or may not be static
    static Point NewCartesian(float x, float y)
    {
        return {x, y};
    }

    static Point NewPolar(float r, float theta)
    {
        return { r*cos(theta), r*sin(theta)}; 
    }
};

int main()
{   
    // Not possible
    // Point p = {1, 2};

    // People may construct a factory itself
    // PointFactory pf;

    // Static call
    auto p = PointFactory::NewPolar(5, M_PI_4);

    Point p2{3, 4}; // Cartesian coordinates

    cout << p << '\n';
    return 0;
}