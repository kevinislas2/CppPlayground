/*
Prototype Coding Exercise

Given the provided code, you are asked to implement Line::deep_copy() to perform a deep copy of the current
Line object
Beware of memory leaks!
*/

#include <iostream>
using std::cout;

struct Point
{
  int x{ 0 }, y{ 0 };

  Point(){}
  
  Point(const int x, const int y) : x{x}, y{y} {}

  ~Point() {
      cout << "Point destructor\n";
  }
};

struct Line
{
  Point *start, *end;
  
  Line(Point* const start, Point* const end)
    : start(start), end(end)
  {
  }

  ~Line()
  {
    delete start;
    delete end;
  }

  Line deep_copy() const
  {
    // Solution
    return { new Point{this->start->x, this->start->y}, new Point{this->end->x, this->end->y}};
  }
};

int main()
{
    Line l1 = {new Point{1, 2}, new Point{2, 3}};
    Line l2 = l1.deep_copy();
}