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
    Grid<double> grid = createGrid<double>(master, 100, 100, 100);

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

    std::ostringstream message;
    message << "Elapsed time: "
            << std::setprecision(5) << timer.getTotal()
            << " (s)\n";
    master.printMessage(message.str());
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
