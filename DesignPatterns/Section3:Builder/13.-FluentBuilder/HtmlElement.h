#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <string>
#include <vector>


using namespace std;

// Utility class for modelling
class HtmlElement
{
    friend class HtmlBuilder;
    string name, text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text) : name(name), text(text) {}
public:
    string str(int indent = 0) const ;

};

#endif