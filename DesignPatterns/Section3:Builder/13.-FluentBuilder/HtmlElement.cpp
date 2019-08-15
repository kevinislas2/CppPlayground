#include <sstream>

#include "HtmlElement.h"
#include "HtmlBuilder.h"

using namespace std;

string HtmlElement::str(int indent) const {
    ostringstream oss;

    string i(indent_size * indent, ' ');

    oss << i << '<' << name << ">\n";

    if(text.size() > 0) {
        oss << string(indent_size*(indent + 1), ' ') << text << endl;
    }

    for (const auto& e : elements) {
        oss << e.str(indent + 1);
    }

    oss << i << "</" << name << ">\n";

    return oss.str();
}