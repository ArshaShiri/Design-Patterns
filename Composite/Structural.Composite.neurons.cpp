#include <cstdio>
#include <vector>
#include <iostream>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
#include <boost/predef/library/c.h>
using namespace std;

struct Neuron;

// CRTP
template <typename Self>
struct SomeNeurons // for both nerurons and a group of neurons
{
  template <typename T> void connect_to(T& other)
  {
    for (Neuron& from : *static_cast<Self*>(this))
    {
      for (Neuron& to : other)
      {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};

struct Neuron : SomeNeurons<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id;

  Neuron()
  {
    static int id = 1; 
    this->id = id++;
  }

  /*template <typename T> void connect_to(T& other)
  {
    for (Neuron& target : other)
      connect_to(target);
  }*/

  // legal in MSVC only
  /*template<> void connect_to<Neuron>(Neuron& other)
  {
    out.push_back(&other);
    other.in.push_back(this);
  }*/

  // connect_to(vector<Neuron>&)

  // To be able to use this class for range base for loop.
  Neuron* begin() { return this; }
  Neuron* end() { return this + 1; }

  friend ostream& operator<<(ostream& os, const Neuron& obj)
  {
    for (Neuron* n : obj.in)
    {
      os << n->id << "\t-->\t[" << obj.id << "]" << endl;
    }

    for (Neuron* n : obj.out)
    {
      os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
  }
};

// A group of neurons
// We should not really inherit from stl because they do not have virtual
// destructor.
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
  NeuronLayer(int count)
  {
    while (count-- > 0)
      emplace_back(Neuron{});
  }

  friend ostream& operator<<(ostream& os, NeuronLayer& obj)
  {
    
    for (auto& n : obj) os << n;
    return os;
  }
};

void main()
{
  Neuron n1, n2;
  n1.connect_to(n2);

  cout << n1 << n2 << endl;

  NeuronLayer l1{5};
  Neuron n3;
  l1.connect_to(n3);
  
  cout << "Neuron " << n3.id << endl << n3 << endl;
  cout << "Layer " << endl << l1 << endl;

  NeuronLayer l2{ 2 }, l3{ 3 };
  l2.connect_to(l3);
  cout << "Layer l2" << endl << l2;
  cout << "Layer l3" << endl << l3;
}