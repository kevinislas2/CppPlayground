//
// Created by joe on 15/08/19.
//

#ifndef INC_15__BUILDERFACETS_PERSONBUILDER_H
#define INC_15__BUILDERFACETS_PERSONBUILDER_H

#include <utility>

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person &person)
            : person {person} {}

public:
    operator Person() const {
        return std::move(person);
    }

    // Builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

};

// Is a base class for PersonJobBuilder and PersonAddressBuilder
class PersonBuilder : public PersonBuilderBase {
    Person p;
public:
    PersonBuilder() : PersonBuilderBase{ p } {};

};


#endif //INC_15__BUILDERFACETS_PERSONBUILDER_H
