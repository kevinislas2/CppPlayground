
#include <iostream>

using namespace std;

class Rectangle
{
protected:
    int width, height;

public:
    Rectangle(int width, int height) : width(width), height(height) {}

    int getWidth() const {
        return width;
    }

    virtual void setWidth(int width) {
        Rectangle::width = width;
    }

    int getHeight() const {
        return height;
    }

    virtual void setHeight(int height) {
        Rectangle::height=height;
    }

    int area() const { return width * height; }
};

void process(Rectangle& r)
{
    int w = r.getWidth();
    r.setHeight(10);

    cout    << "expected area = " << (w*10)
            << ", got " << r.area() << '\n';
}

/*
Violates Liskov substitution because now Square does not work well with process (which receives the base class Rectangle)
*/
class Square : public Rectangle
{
public:
    Square(int size) : Rectangle(size, size) {};

    void setWidth(int width) override {
        this->width = this->height = width;
    }

    void setHeight(int height) override {
        this->height = this->width = height;
    }
};

// We can solve it by introducing a factory pattern
struct RectangleFactory
{
    static Rectangle create_rectangle(int w, int h);
    static Rectangle create_square(int size);
};

int main() {

    Rectangle r{3, 4};
    process(r);

    Square sq{5};
    process(sq);

    return 0;
}