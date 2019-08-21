/*
Group geometric shapes using Composite design pattern
*/

#include <iostream>
#include <vector>

using namespace std;

struct GraphicObject
{
    virtual void draw() = 0;
};

struct Circle : GraphicObject
{
    void draw() override {
        cout << "Circle\n";
    }
};

struct Group: GraphicObject
{
    string name;
    vector<GraphicObject*> objects;

    Group(const string& name) : name(name) {}

    void draw() override
    {
        cout << "Group " << name.c_str() << " contains:\n";
        for (auto&& o : objects) {
            o->draw();
        }
    }
};

int main()
{
    Group root("root");
    Circle c1, c2;

    root.objects.push_back(&c1);

    Group subgroup("sub");
    subgroup.objects.push_back(&c2);

    root.objects.push_back(&subgroup);

    root.draw();

    return 0;
}