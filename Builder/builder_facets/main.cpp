#include <iostream>

#include "person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main 
{
  Person p = Person::create()
    .lives().at("").with_postcode("").in("")
    .works().at("").as_a("").earning(141);

  return 0;
}