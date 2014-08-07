#include <iostream>
#include <iomanip>
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
    auto grid = createGrid<double>(master, 100, 100, 100, 3);

    auto a = createField<double>(master, grid, "a");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    Timer timer(master, "Diffusion (CPU)");
    timer.start();
    for(int n=0; n<1000; ++n)
      a += b;
    timer.end();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
