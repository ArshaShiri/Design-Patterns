#pragma once
#include <string>

struct Person
{
  std::string name;

  struct PersonImpl;
  PersonImpl *impl; // bridge - not necessarily inner class, can vary

  Person();
  ~Person();

  // Implementation would be bridged in a separate class. 
  void greet();
};
