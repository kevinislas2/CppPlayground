#ifndef HTMLBUILDER_H
#define HTMLBUILDER_H

#include <string>
#include <utility>

#include "HtmlElement.h"

using namespace std;

// The actual builder
struct HtmlBuilder 
{
    HtmlElement root;
    
    HtmlBuilder(string root_name) {
        root.name = root_name;
    };

    HtmlBuilder& add_child(string child_name, string child_text);

    string str() const;


    static HtmlBuilder build(string root_name) {

        return HtmlBuilder(root_name);
    }

    operator HtmlElement() const {return move(root);}

    HtmlBuilder
};

#endif