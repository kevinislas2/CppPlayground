/*
Example of where a Factory pattern might come in handy.
*/
#include <iostream>
#include <cmath>

using namespace std;

enum class PointType
{
    cartesian,
    polar
};

struct Point
{
    float x, y;

    Point(float a, float b, PointType type = PointType::cartesian)
    {
        if(type == PointType::cartesian)
        {
            x = a;
            y = b;
        } else {
            // Transform coordinates

            x = a * cos(b);
            y = b * sin(b);
        }
    }
    // Point(float x, float y) : x{x}, y{y} {}

    //Polar coordinates (Cannot overload)
    // Point(float rho, float theta)
    // {

    // }
};

int main()
{
    return 0;
}