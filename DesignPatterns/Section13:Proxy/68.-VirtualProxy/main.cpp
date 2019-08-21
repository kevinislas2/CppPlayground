
#include <iostream>
#include <string>

using namespace std;

struct Image
{
    virtual void draw() = 0;
};

// Instead of eagerly loading the bitmap we could defer it until draw
// Imagine that we cant modify Bitmap behaviour so we define a proxy
struct Bitmap : Image
{
    Bitmap(const string& filename)
    {
        cout << "Loading bitmap from " << filename << '\n';
    }

    void draw() override {
        cout << "Drawing bitmap\n";
    }
};

struct LazyBitmap : Image
{
    LazyBitmap(const string& filename)
        : filename{filename}
        {}
    
    ~LazyBitmap() {
        if(bmp) {
            delete bmp;
        }
    }

    void draw() override {
        if(!bmp) {
            bmp = new Bitmap(filename);
        }
        bmp->draw();
    }
private:
    string filename;
    Bitmap* bmp{nullptr};
};

int main()
{

    Bitmap bmp{"pokemon.png"};
    bmp.draw();

    // bmp is only loaded when draw is called
    LazyBitmap bmp{"pokemon.png"};
    bmp.draw();
    return 0;
}