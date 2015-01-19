/*
 * BigDataGrid
 * Copyright (c) 2014-2015 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigDataGrid are derived from
 * MicroHH (https://github.com/MicroHH)
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

#include <thrust/device_vector.h>
#include <cstdio>
#include "DiffusionGPU.h"
#include "Master.h"
#include "Grid.h"

template<class TGrid, class TField>
DiffusionGPU<TGrid,TField>::DiffusionGPU(Grid<TGrid> &gridin) :
  grid(gridin)
{
  Master &master = Master::getInstance();
  master.printMessage("Constructed DiffusionGPU\n");
}

template<class TGrid, class TField>
DiffusionGPU<TGrid,TField>::~DiffusionGPU()
{
  Master &master = Master::getInstance();
  master.printMessage("Destructed DiffusionGPU\n");
}

template<class TField>
__global__ void execDiffusion(TField * __restrict__ at, TField * __restrict__ a, const GridDims dims)
{
  const TField c0 = -1460./576.;
  const TField c1 =   783./576.;
  const TField c2 =   -54./576.;
  const TField c3 =     1./576.;

  long ijk,ii1,ii2,ii3,jj1,jj2,jj3,kk1,kk2,kk3;
  long i = blockIdx.x*blockDim.x + threadIdx.x + dims.istart;
  long j = blockIdx.y*blockDim.y + threadIdx.y + dims.jstart;
  long k = blockIdx.z + dims.kstart;

  ii1 = 1;
  ii2 = 2;
  ii3 = 3;
  jj1 = 1*dims.icells;
  jj2 = 2*dims.icells;
  jj3 = 3*dims.icells;
  kk1 = 1*dims.ijcells;
  kk2 = 2*dims.ijcells;
  kk3 = 3*dims.ijcells;

  // only perform the kernel if the coordinate is in the 3d field
  if(i < dims.iend && j < dims.jend && k < dims.kend)
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

template<class TGrid, class TField>
void DiffusionGPU<TGrid,TField>::exec(thrust::device_vector<TField> &at_gpu, thrust::device_vector<TField> &a_gpu)
{
  const GridDims dims = grid.getDims();
  TField *at = thrust::raw_pointer_cast(at_gpu.data());
  TField *a  = thrust::raw_pointer_cast(a_gpu .data());

  const int blocki = 128;
  const int blockj = 2;
  const int gridi = dims.itot/blocki + (dims.itot%blocki > 0);
  const int gridj = dims.jtot/blockj + (dims.jtot%blockj > 0);

  dim3 grid (gridi, gridj, dims.ktot);
  dim3 block(blocki, blockj, 1);

  execDiffusion<<<grid, block>>>(at, a, dims);
}
