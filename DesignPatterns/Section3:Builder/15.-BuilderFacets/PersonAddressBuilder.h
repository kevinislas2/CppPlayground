//
// Created by joe on 15/08/19.
//

#ifndef INC_15__BUILDERFACETS_PERSONADDRESSBUILDER_H
#define INC_15__BUILDERFACETS_PERSONADDRESSBUILDER_H

#include "PersonBuilder.h" // Why does PersonAddressBuilder doesnt need to import PersonBuilder but PersonJobBuilder does?
#include <string>

class PersonAddressBuilder : public PersonBuilderBase {
    typedef PersonAddressBuilder Self;
public:
    explicit PersonAddressBuilder(Person& person) : PersonBuilderBase(person) {}

    Self& at(std::string street_address)
    {
        person.street_address = street_address;
        return *this;
    }

    Self& with_postcode(std::string post_code)
    {
        person.post_code = post_code;
        return *this;
    }

    Self& in(std::string city)
    {
        person.city = city;
        return *this;
    }
};


#endif //INC_15__BUILDERFACETS_PERSONADDRESSBUILDER_H
