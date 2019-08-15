#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>

using namespace std;

// Utility class for modelling
struct HtmlElement
{
    string name, text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text) : name(name), text(text) {}

    string str(int indent = 0) const ;
};

#endif