#pragma once
#include "HotDrink.h"


// Abstract factory.
struct HotDrinkFactory 
{
  virtual unique_ptr<HotDrink> make() const = 0;
};