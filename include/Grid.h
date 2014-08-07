/*
 * BigData4D
 * Copyright (c) 2014 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigData4D are derived from
 * MicroHH (https://github.com/MicroHH)
 *
 * This file is part of BigData4D
 *
 * BigData4D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * BigData4D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with BigData4D.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GRID
#define GRID

#include <vector>

class Master;

struct GridDims
{
  long itot;
  long jtot;
  long ktot;
  long ntot;

  long icells;
  long jcells;
  long kcells;

  long ijcells;
  long ncells;

  long istart;
  long jstart;
  long kstart;

  long iend;
  long jend;
  long kend;
};

template<class T>
struct GridVars
{
  std::vector<T> x;
  std::vector<T> y;
  std::vector<T> z;
};

template<class T>
class Grid
{
  public:
    Grid(Master &, GridDims &, GridVars<T> &);
    virtual ~Grid();

    const GridDims getDims();
    long getncells();

  protected:
    Master &master;
    const GridDims dims;
    const GridVars<T> vars;
};

template<class T>
Grid<T> createGrid(Master &, long, long, long, long gc=0);

#include "Grid.hxx"
#endif
