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

#include <thrust/device_vector.h>
#include "DiffusionGPU.h"
#include "Master.h"
#include "Grid.h"

template<class T, class TF>
DiffusionGPU<T,TF>::DiffusionGPU(Master &masterin, Grid<T> &gridin) :
  master(masterin),
  grid(gridin)
{
  master.printMessage("Constructed DiffusionGPU\n");
}

template<class TF>
__global__ void execDiffusion(TF * __restrict__ at, TF * __restrict__ a)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  int j = blockIdx.y*blockDim.y + threadIdx.y;
  int k = blockIdx.z;

  int ijk = i + j + k;
}

/*
void DiffusionGPU<T,TF>::execDiffusion(TF * const restrict at, const TF * const restrict a, const GridDims &dims)
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

  // fill field with random numbers
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
}*/

template<class T, class TF>
void DiffusionGPU<T,TF>::exec(thrust::device_vector<TF> &at_gpu, thrust::device_vector<TF> &a_gpu)
{
  const GridDims dims = grid.getDims();
  TF *at = thrust::raw_pointer_cast(at_gpu.data());
  TF *a  = thrust::raw_pointer_cast(a_gpu .data());

  dim3 grid (1,1,1);
  dim3 block(1,1,1);

  execDiffusion<<<grid, block>>>(at, a);
}

template<class T, class TF>
DiffusionGPU<T,TF>::~DiffusionGPU()
{
  master.printMessage("Destructed Grid\n");
}