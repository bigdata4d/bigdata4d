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

#ifndef DIFFUSION
#define DIFFUSION

#include <thread>
#include "Master.h"
#include "Field.h"
#include "Grid.h"

template<class T, class TF>
class Diffusion
{
  public:
    Diffusion(Grid<T> &);
    virtual ~Diffusion();

    virtual void exec(Field<TF,T>&, const Field<TF,T>&, bool);

  protected:
    Grid<T> &grid;

  private:
    void execDiffusion(TF * const, const TF * const, const GridDims);
};

// IMPLEMENTATION BELOW
template<class T, class TF>
inline Diffusion<T,TF>::Diffusion(Grid<T> &gridin) :
  grid(gridin)
{
  Master &master = Master::getInstance();
  master.printMessage("Constructed Diffusion\n");
}

template<class T, class TF>
inline void Diffusion<T,TF>::execDiffusion(TF * const restrict at, const TF * const restrict a, const GridDims dims)
{
  long ijk,ii1,ii2,ii3,jj1,jj2,jj3,kk1,kk2,kk3;
  ii1 = 1;
  ii2 = 2;
  ii3 = 3;
  jj1 = 1*dims.icells;
  jj2 = 2*dims.icells;
  jj3 = 3*dims.icells;
  kk1 = 1*dims.ijcells;
  kk2 = 2*dims.ijcells;
  kk3 = 3*dims.ijcells;

  const T c0 = -1460./576.;
  const T c1 =   783./576.;
  const T c2 =   -54./576.;
  const T c3 =     1./576.;

  for(long k=dims.kstart; k<dims.kend; ++k)
    for(long j=dims.jstart; j<dims.jend; ++j)
      for(long i=dims.istart; i<dims.iend; ++i)
      {
        ijk = i + j*jj1 + k*kk1;
        at[ijk] += c3*a[ijk-ii3] + c2*a[ijk-ii2] + c1*a[ijk-ii1] + c0*a[ijk] 
                 + c3*a[ijk+ii1] + c2*a[ijk+ii2] + c1*a[ijk+ii3]
                 + c3*a[ijk-jj3] + c2*a[ijk-jj2] + c1*a[ijk-jj1] + c0*a[ijk] 
                 + c3*a[ijk+jj1] + c2*a[ijk+jj2] + c1*a[ijk+jj3]
                 + c3*a[ijk-kk3] + c2*a[ijk-kk2] + c1*a[ijk-kk1] + c0*a[ijk] 
                 + c3*a[ijk+kk1] + c2*a[ijk+kk2] + c1*a[ijk+kk3];
      }
}

template<class T, class TF>
inline void Diffusion<T,TF>::exec(Field<TF,T>& at, const Field<TF,T>& a, const bool threaded)
{
  const GridDims dims = grid.getDims();
  if (threaded)
  {
    std::thread t1(&Diffusion<T,TF>::execDiffusion, this, &at.data[0], &a.data[0], dims);
    // std::thread t2(&Diffusion<T,TF>::execDiffusion, this, &at.data[0], &a.data[0], dims);
    t1.join();
    // t2.join();
  }
  else
    execDiffusion(&at.data[0], &a.data[0], dims);
}

template<class T, class TF>
inline Diffusion<T,TF>::~Diffusion()
{
  Master &master = Master::getInstance();
  master.printMessage("Destructed Diffusion\n");
}
#endif
