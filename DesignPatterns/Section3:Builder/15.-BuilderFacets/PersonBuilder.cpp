//
// Created by joe on 15/08/19.
//

#include "PersonBuilder.h"
#include "PersonJobBuilder.h"
#include "PersonAddressBuilder.h"

PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder{ person };
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{ person };
}
