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

#include "Diffusion.h"
#include "Master.h"
#include "Grid.h"

template<class T>
Diffusion<T>::Diffusion(Master &masterin, Grid<T> &gridin) :
  master(masterin),
  grid(gridin)
{
}

template<class T>
void Diffusion<T>::exec(Field &at, const Field &a)
{
  const GridDims dims = grid.getDims();

  long
  ii1 = 1;
  ii2 = 2;
  ii3 = 3;
  jj1 = 1*dims.icells;
  jj2 = 2*dims.icells;
  jj3 = 3*dims.icells;
  kk1 = 1*dims.ijcells;
  kk2 = 2*dims.ijcells;
  kk3 = 3*dims.ijcells;

  // fill field with random numbers
  for(long k=dims.kstart; k<dims.kend; ++k)
    for(long j=dims.jstart; j<dims.jend; ++j)
      for(long i=dims.istart; i<dims.iend; ++i)
      {
        long ijk = i + j*dims.icells + k*dims.ijcells;
        at.data[ijk] = a.data[ijk-ii3] + a.data[ijk-ii2] + a.data[ijk-ii1] + a.data[ijk] 
                     + a.data[ijk+ii1] + a.data[ijk+ii2] + a.data[ijk+ii3] 
                     + a.data[ijk-jj3] + a.data[ijk-jj2] + a.data[ijk-jj1] + a.data[ijk]
                     + a.data[ijk+jj1] + a.data[ijk+jj2] + a.data[ijk+jj3] 
                     + a.data[ijk-kk3] + a.data[ijk-kk2] + a.data[ijk-kk1] + a.data[ijk]
                     + a.data[ijk+kk1] + a.data[ijk+kk2] + a.data[ijk+kk3];
      }
}

template<class T>
Diffusion<T>::~Diffusion()
{
}
