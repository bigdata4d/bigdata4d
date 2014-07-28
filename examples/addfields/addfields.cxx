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
    Grid grid(master, 2, 2, 2);

    Field<int> a(master, grid, "a");
    Field<int> b(master, grid, "b");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    // test the copy operator
    Field<int> aa(master, grid, "aa");
    aa = a;

    // test the assignment operator
    Field<int> bb(b);

    // test the compound addition operator
    Field<int> c = a;
    c += b;

    // test the addition operator
    Field<int> d = a + b + c;

    Field<int> e(master, grid, "e");
    e = a + b + c;

    for(int i=0; i<a.data.size(); ++i)
      std::printf("CvH, %d: %d, %d, %d, %d, %d, %d, %d\n",
          i, a.data[i], aa.data[i], b.data[i], bb.data[i], c.data[i], d.data[i], e.data[i]);
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
