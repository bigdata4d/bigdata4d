#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Grid.h"
#include "Field.h"
#include "Timer.h"

int main(int argc, char *argv[])
{
  try
  {
    auto grid = createGrid<double>(100, 100, 100);

    auto a = createField<double>(grid, "a");
    auto b = createField<double>(grid, "b");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    for(auto &i : b.data)
      i = std::rand() % 10;

    Timer timer("a += b");
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
