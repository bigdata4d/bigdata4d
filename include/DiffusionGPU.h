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

#ifndef DIFFUSIONGPU
#define DIFFUSIONGPU

#include "Field.h"
#include "Grid.h"

template<class T, class TF>
class DiffusionGPU
{
  public:
    DiffusionGPU(Grid<T> &);
    virtual ~DiffusionGPU();

    void exec(thrust::device_vector<TF> &at_gpu, thrust::device_vector<TF> &a_gpu);

  protected:
    Grid<T> &grid;

  private:
    // __global__ void execDiffusion(TF *, TF *);
};

#include "DiffusionGPU.hxx"
#endif
