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

#ifndef DIFFUSION
#define DIFFUSION

#include "Field.h"
#include "Grid.h"

template<class T, class TF>
class Diffusion
{
  public:
    Diffusion(Grid<T> &);
    virtual ~Diffusion();

    virtual void exec(Field<TF,T> &, const Field<TF,T> &);

  protected:
    Grid<T> &grid;

  private:
    void execDiffusion(TF * const, const TF * const, const GridDims &);
};

#include "Diffusion.hxx"
#endif
