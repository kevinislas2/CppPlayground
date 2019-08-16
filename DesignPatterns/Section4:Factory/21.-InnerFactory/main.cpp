/*
Inner factory
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
    Point(float x, float y) : x{x}, y{y} {}

    float x, y;

    class PointFactory
    {
    private:
        PointFactory() {}
    public:
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

public:
    friend ostream &operator<<(ostream& os, const Point& point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

    //This is better, since we solve the OCP problem by defining factory inside Point
    //This also makes points construction 
    // struct PointFactory
    // {
    //     // May or may not be static
    //     static Point NewCartesian(float x, float y)
    //     {
    //         return {x, y};
    //     }

    //     static Point NewPolar(float r, float theta)
    //     {
    //         return { r*cos(theta), r*sin(theta)}; 
    //     }
    // };

    // Or even better, make a singleton factory
    static PointFactory Factory;

};

int main()
{   
    // Static call
    // auto p = Point::PointFactory::NewPolar(5, M_PI_4);
    auto p = Point::Factory.NewPolar(5, M_PI_4);
    cout << p << '\n';

    return 0;
}