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

#include <vector>
#include <sstream>
#include "Grid.h"
#include "Master.h"

template<class T>
Grid<T>::Grid(Master &masterin, GridDims &dimsin, GridVars<T> &varsin) :
  master(masterin),
  dims(dimsin),
  vars(varsin)
{
  master.printMessage("Constructed Grid\n");
}

template<class T>
Grid<T>::~Grid()
{
  master.printMessage("Destructed Grid\n");
}

template<class T>
GridDims Grid<T>::getDims()
{
  return dims;
}

template<class T>
long Grid<T>::getncells()
{
  return dims.ncells;
}

template<class T>
Grid<T> createGrid(Master &masterin, long itotin, long jtotin, long ktotin, long gc)
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
  
  return Grid<T>(masterin, dims, vars);
}
