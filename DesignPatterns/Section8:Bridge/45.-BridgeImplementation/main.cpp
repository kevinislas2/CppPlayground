
// Shapes - circle, square
// Renderer - raster (points), vector (lines)

// 2x2 RasterCircleRenderer, RasterSquareRenderer, VectorCircleRenderer, VectorSquareRenderer

/*
By shape having a Renderer member instead of inheriting from it, we can provide various functionality
without definining extra Shape classes
*/
#include <iostream>

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;

};

struct RasterRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rastering a circle of radius " << radius << '\n';
    }
};

struct VectorRenderer : Renderer
{
    void render_circle(float x, float y, float radius) override
    {
        std::cout << "Drvectorawing a vector circle of radius " << radius << '\n';
    }
};

struct Shape
{
protected:
    Renderer& renderer;
    Shape(Renderer& renderer) : renderer(renderer) {}
public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    float x, y, radius;
    Circle(Renderer& renderer, float x, float y, float radius) 
        : Shape(renderer), x{x}, y{y}, radius{radius} 
        {}

    void draw() override {
        renderer.render_circle(x, y, radius);
    }

    void resize(float factor) override {
        radius *= factor;
    }


};

int main() {

    RasterRenderer rr;                  //This is the bridge
    Circle raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(2);
    raster_circle.draw();
    return 0;
}