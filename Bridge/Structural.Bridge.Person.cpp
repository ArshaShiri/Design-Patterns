// Pimple Idiom
// hiding the implementation of a particular class by sticking it to its 
// implementation.
// By this we are hiding the details of the implementation.
// The details go to the cpp files and are not provided to the client of the code.


#include "Person.h"

struct Person::PersonImpl
{
  void greet(Person* p);
};

void Person::PersonImpl::greet(Person* p)
{
  printf("hello %s", p->name.c_str());
}

Person::Person()
  : impl(new PersonImpl)
{
}

Person::~Person()
{
  delete impl;
}

void Person::greet()
{
  impl->greet(this);
}


