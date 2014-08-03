#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Grid grid = createGrid(master, 1, 1, 10);

    Field<double> a(master, grid, "a");
    Field<double> b(master, grid, "b");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    // test the copy operator
    Field<double> aa(master, grid, "aa");
    aa = a;

    // test the assignment operator
    Field<double> bb(b);

    // test the compound addition operator
    Field<double> c = a;
    c += b;

    // test the addition operator
    Field<double> d(master, grid, "d");
    d = a + b + c;

    Field<double> e = a + b + c;

    for(int n=0; n<a.data.size(); ++n)
    {
      std::ostringstream message;
      message << std::setw(2);
      message << n << " = {" 
        << std::setw(6) <<  a.data[n] << ", "
        << std::setw(6) << aa.data[n] << ", "
        << std::setw(6) <<  b.data[n] << ", "
        << std::setw(6) << bb.data[n] << ", "
        << std::setw(6) <<  c.data[n] << ", "
        << std::setw(6) <<  d.data[n] << ", "
        << std::setw(6) <<  e.data[n] << " }\n";
      master.printMessage(message.str());
    }
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
