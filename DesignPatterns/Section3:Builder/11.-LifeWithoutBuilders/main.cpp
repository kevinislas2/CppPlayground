
/*
Example on where a Builder might be appropiate
*/

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    // Not efficient
    auto text = "hello";
    string output;
    output += "<p>";
    output += text;
    output += "</p>";
    cout << output << '\n';

    // Still follows the idea of putting a string together piecewise
    string words[] = {"hello", "world"};
    ostringstream oss;
    oss << "<ul>\n";
    for(auto& w : words) {
        oss << "\t<li>" << w << "</li>\n";
    }
    oss << "</ul>";
    cout << oss.str() << '\n';

    // HTML has rules about the use of tags which are not reflected in this code
    // We could enforce them by creating an HTMLBuilder which follows those rules
    // Using OOP

    return 0;
}