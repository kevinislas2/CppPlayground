//
// Created by joe on 15/08/19.
//

#include "Person.h"
#include "PersonBuilder.h"

PersonBuilder Person::create() {
    return PersonBuilder{};
}
