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

    Field a(master, grid);
    Field b(master, grid);

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    // test the copy operator
    Field aa(master, grid);
    aa = a;

    // test the assignment operator
    Field bb(b);

    // test the compound addition operator
    Field c = a;
    c += b;

    // test the addition operator
    Field d = a + b + c;

    Field e(master,grid);
    e = a + b + c;

    Field f(master,grid);
    f.addFields(a, b, c);


    for(int i=0; i<a.data.size(); ++i)
      std::printf("CvH, %d: %d, %d, %d, %d, %d, %d, %d, %d\n",
          i, a.data[i], aa.data[i], b.data[i], bb.data[i], c.data[i], d.data[i], e.data[i], f.data[i]);
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
