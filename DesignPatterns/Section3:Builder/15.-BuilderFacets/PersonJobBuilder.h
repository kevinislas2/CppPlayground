//
// Created by joe on 15/08/19.
//

#ifndef INC_15__BUILDERFACETS_PERSONJOBBUILDER_H
#define INC_15__BUILDERFACETS_PERSONJOBBUILDER_H

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase {
    typedef PersonJobBuilder Self;
public:
    explicit PersonJobBuilder(Person& person) : PersonBuilderBase(person) {}

    Self& at(std::string company_name)
    {
        person.company_name = company_name;
        return *this;
    }

    Self& as_a(std::string position)
    {
        person.position = position;
        return *this;
    }

    Self& earning(int annual_income)
    {
        person.annual_income = annual_income;
        return *this;
    }
};


#endif //INC_15__BUILDERFACETS_PERSONJOBBUILDER_H
