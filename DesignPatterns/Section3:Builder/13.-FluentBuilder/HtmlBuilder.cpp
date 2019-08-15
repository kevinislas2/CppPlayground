#include "HtmlBuilder.h"

HtmlBuilder& HtmlBuilder::add_child(string child_name, string child_text) {
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);
    return *this;
}

string HtmlBuilder::str() const {return root.str(); }