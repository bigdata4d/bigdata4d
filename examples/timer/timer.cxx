/*
 * BigDataGrid
 * Copyright (c) 2014-2015 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigDataGrid are derived from
 * MicroHH (https://github.com/microhh)
 *
 * This file is part of BigDataGrid
 *
 * BigDataGrid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * BigDataGrid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with BigDataGrid.  If not, see <http://www.gnu.org/licenses/>.
 */

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
