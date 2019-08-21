
/*
Rose can be red, blu or red and blue. Given the class interface Flower and class Rose, build decorators RedFlower and
BlueFlower that would print the following:

Does not work when Red{Blue{Red{Rose{}}}}
Expected: "Red-Blue"
Got: Blue-Red
*/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Flower
{
    virtual string str() = 0;
};

struct Rose : Flower{
    string str() override {
        return "A rose";
    }
};

struct BlueFlower;

struct RedFlower: Rose
{
public:
    RedFlower(const Rose& rose)
        : rose{rose}, description{"red"} {}
    
    RedFlower(const RedFlower& other) 
        : rose{other.rose}, description{other.description}
        {}

    RedFlower(const BlueFlower& other);

    string str() override {
        stringstream ss{};
        ss << rose.str() << " that is " << description[0];

        for(size_t i = 1; i < description.size(); ++i) {
            ss << " and " << description[i];
        }
        return ss.str();
    }
    
    Rose rose;
    vector<string> description;
};

struct BlueFlower : Rose
{
public:
    BlueFlower(const Rose& rose)
        : rose{rose}
        {   
            description.push_back("blue");
        }

    BlueFlower(const BlueFlower& other) 
        : rose{other.rose}, description{other.description}
        {}

    BlueFlower(const RedFlower& other)
        : rose{other.rose}, description{other.description} {
        
        if(description.size() < 2) {
            description.push_back("blue");
        }

    }
    
    string str() override {
        stringstream ss{};
        ss << rose.str() << " that is " << description[0];

        for(size_t i = 1; i < description.size(); ++i) {
            ss << " and " << description[i];
        }
        return ss.str();
    }

    Rose rose;
    vector<string> description;
};

RedFlower::RedFlower(const BlueFlower& other)
    : rose{other.rose}, description{other.description}
{
    if(description.size() < 2) {
        description.push_back("red");
    }
}

int main()
{

    Rose rose;
    RedFlower red_rose{rose};
    RedFlower red_red_rose{red_rose};
    BlueFlower blue_flower{rose};
    BlueFlower blue_red_rose{red_rose};

    
    RedFlower red_blue_rose{blue_flower};

    RedFlower complicated{RedFlower{BlueFlower{RedFlower{Rose{}}}}};
    
    cout << rose.str() << '\n';
    cout << red_rose.str() << '\n';
    cout << red_red_rose.str() << '\n';
    cout << blue_flower.str() << '\n';
    cout << blue_red_rose.str() << '\n';
    cout << red_blue_rose.str() << '\n';
    cout << complicated.str() << '\n';
    return 0;
}