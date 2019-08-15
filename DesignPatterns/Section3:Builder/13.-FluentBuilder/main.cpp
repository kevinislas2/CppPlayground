
/*
Add fluent interface to builder: Compiles with -std=c++17
*/
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "HtmlBuilder.h"
#include "HtmlElement.h"

using namespace std;

int main()
{

    HtmlBuilder builder{"ul"};
    builder.add_child("li", "hello").add_child("li", "world");
    cout << builder.str() << '\n';

    HtmlBuilder builder2{"ul"};
    builder2.add_child("li", "hello").add_child("li", "world");
    cout << builder2.str() << '\n';

    HtmlElement builderAuto = HtmlBuilder::build("ul").add_child("Second", "Node");

    cout << builderAuto.str() << '\n';
    return 0;
}