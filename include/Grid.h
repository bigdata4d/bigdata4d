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

#ifndef GRID
#define GRID

#include <vector>
#include <sstream>
#include "Master.h"

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
    Grid(GridDims &, GridVars<T> &);
    ~Grid();

    const GridDims getDims();
    long getncells();

  protected:
    const GridDims dims;
    const GridVars<T> vars;
};

template<class T>
Grid<T> createGrid(long, long, long, long gc=0);


// IMPLEMENTATION BELOW
template<class T>
inline Grid<T>::Grid(GridDims &dimsin, GridVars<T> &varsin) :
  dims(dimsin),
  vars(varsin)
{
  Master &master = Master::getInstance();
  master.printMessage("Constructed Grid\n");
}

template<class T>
inline Grid<T>::~Grid()
{
  Master &master = Master::getInstance();
  master.printMessage("Destructed Grid\n");
}

template<class T>
inline const GridDims Grid<T>::getDims()
{
  return dims;
}

template<class T>
inline long Grid<T>::getncells()
{
  return dims.ncells;
}

template<class T>
inline Grid<T> createGrid(long itotin, long jtotin, long ktotin, long gc)
{
  long ntot = itotin*jtotin*ktotin;

  GridDims dims;
  dims.itot = itotin;
  dims.jtot = jtotin;
  dims.ktot = ktotin;
  dims.ntot = ntot;

  dims.icells = dims.itot + 2*gc;
  dims.jcells = dims.jtot + 2*gc;
  dims.kcells = dims.ktot + 2*gc;

  dims.ijcells = dims.icells * dims.jcells;
  dims.ncells  = dims.icells * dims.jcells * dims.kcells;

  dims.istart = gc;
  dims.jstart = gc;
  dims.kstart = gc;

  dims.iend = dims.itot + gc;
  dims.jend = dims.jtot + gc;
  dims.kend = dims.ktot + gc;

  GridVars<T> vars;
  for(int i=0; i<dims.itot; ++i) {
    vars.x.push_back((0.5+i)/dims.itot); }
  for(int j=0; j<dims.jtot; ++j) {
    vars.y.push_back((0.5+j)/dims.jtot); }
  for(int k=0; k<dims.ktot; ++k) {
    vars.z.push_back((0.5+k)/dims.ktot); }
  
  return Grid<T>(dims, vars);
}
#endif
