#include "headers.h"

// Singleton printer using only static variables (bad idea)
class Printer
{
    static int id;
public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
};

int main()
{

    Printer p;
    int id = p.get_id();

    return 0;
}
