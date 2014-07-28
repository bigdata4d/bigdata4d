#include <iostream>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Grid grid(master, 1, 1, 3);

    Field<float> a(master, grid, "a");
    Field<float> b(master, grid, "b");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    // test the copy operator
    Field<float> aa(master, grid, "aa");
    aa = a;

    // test the assignment operator
    Field<float> bb(b);

    // test the compound addition operator
    Field<float> c = a;
    c += b;

    // test the addition operator
    Field<float> d(master, grid, "d");
    d = a + b + c;

    Field<float> e = a + b + c;

    for(int i=0; i<a.data.size(); ++i)
      std::printf("CvH, %d: %E, %E, %E, %E, %E, %E, %E\n",
          i, a.data[i], aa.data[i], b.data[i], bb.data[i], c.data[i], d.data[i], e.data[i]);
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
