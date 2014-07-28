#include <iostream>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Timer.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Grid grid(master, 100, 100, 100);

    Field<double> a(master, grid, "a");
    Field<double> b(master, grid, "b");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    Timer timer(master);
    timer.start();
    for(int n=0; n<1000; ++n)
      a += b;
    timer.end();

    std::printf("Elapsed time: %E (s)\n", timer.getTotal());
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
