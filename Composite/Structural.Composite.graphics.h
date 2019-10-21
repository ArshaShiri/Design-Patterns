#pragma once
#include <iostream>
#include <vector>
#include <memory>

struct GraphicObject
{
  virtual void draw() = 0;
};

struct Circle : GraphicObject
{
  void draw() override
  {
    std::cout << "Circle" << std::endl;
  }
};

// We can group several circles.
// Composite of the other obeject (circle) and they have the can be used in a uniform manner 
// which is draw in this example. 
struct Group : GraphicObject
{
  std::string name;


  explicit Group(const std::string& name)
    : name{name}
  {
  }

  void draw() override
  {
    std::cout << "Group " << name.c_str() << " contains:" << std::endl;
    for (auto&& o : objects)
      o->draw();
  }

  std::vector<GraphicObject*> objects;
};

inline void graphics()
{
  Group root("root");
  Circle c1, c2;
  root.objects.push_back(&c1);

  // Groups of groups
  Group subgroup("sub");
  subgroup.objects.push_back(&c2);

  root.objects.push_back(&subgroup);

  root.draw();
}