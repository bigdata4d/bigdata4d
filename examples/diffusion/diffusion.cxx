#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Diffusion.h"
#include "Timer.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    auto grid = createGrid<double>(master, 100, 100, 100, 3);

    auto a  = createField<double>(master, grid, "a");
    auto at = createField<double>(master, grid, "a");

    a.randomize(10);

    Diffusion<double,double> diff(master, grid);

    Timer timer(master, "Diffusion (CPU)");
    timer.start();
    for(int n=0; n<500; ++n)
      diff.exec(at, a);
    timer.end();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
