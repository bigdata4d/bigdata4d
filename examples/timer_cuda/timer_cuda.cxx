#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Timer.h"

// CUDA functions
void hello(Master &);

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Grid grid(master, 100, 100, 100);

    Field<float> a(master, grid, "a");
    Field<float> b(master, grid, "b");

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

    hello(master);

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
