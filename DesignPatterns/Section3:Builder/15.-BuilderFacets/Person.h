//
// Created by joe on 15/08/19.
//

#ifndef INC_15__BUILDERFACETS_PERSON_H
#define INC_15__BUILDERFACETS_PERSON_H

#include <string>
#include <iostream>

class PersonBuilder;

class Person {
    // address
    std::string street_address, post_code, city;

    // employment
    std::string company_name, position;
    int annual_income = 0;

    Person()
    {
        std::cout << "Person created\n";
    }

public:
    ~Person()
    {
        std::cout << "Person destroyed\n";
    }
    static PersonBuilder create();

    // Copy constructor
    Person(Person&& other)
            : street_address{move(other.street_address)},
              post_code{move(other.post_code)},
              city{move(other.city)},
              company_name{move(other.company_name)},
              position{move(other.position)},
              annual_income{other.annual_income}
    {
        std::cout << "Copy constructor\n";
    }

    // Copy Assignment
    Person& operator=(Person&& other)
    {
        std::cout << "Copy assignment\n";
        if (this == &other)
            return *this;
        street_address = move(other.street_address);
        post_code = move(other.post_code);
        city = move(other.city);
        company_name = move(other.company_name);
        position = move(other.position);
        annual_income = other.annual_income;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& obj)
    {
        return os
                << "street_address: " << obj.street_address << '\n'
                << "post_code: " << obj.post_code << '\n'
                << "city: " << obj.city << '\n'
                << "company_name: " << obj.company_name << '\n'
                << "position: " << obj.position << '\n'
                << "annual_income: " << obj.annual_income << '\n';
    }

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
};


#endif //INC_15__BUILDERFACETS_PERSON_H
