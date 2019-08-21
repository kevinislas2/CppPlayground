/*
You are given a Rectangle protocol and an extension method on it. Try to define a SquareToRectangleAdapter that
adapts the Square to the Rectangle interface
*/

#include <iostream>

struct Square
{
  int side{ 0 };


  explicit Square(const int side)
    : side(side)
  {
  }
};

struct Rectangle
{
  virtual int width() const = 0;
  virtual int height() const = 0;

  int area() const
  {
    return width() * height();
  }
};

struct SquareToRectangleAdapter : Rectangle
{
  int side { 0 };
  
  SquareToRectangleAdapter(const Square& square)
  : side {square.side}
  {
  }
  // todo
  
  virtual int width() const {
      return side;
  }
  
  virtual int height() const {
      return side;
  }
};

int main() {
    Square sq = Square{10};

    SquareToRectangleAdapter rect = SquareToRectangleAdapter{sq};

    std::cout << rect.area() << '\n';
    return 0;
}