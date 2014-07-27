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
#include "Field.h"
#include "Master.h"
#include "Grid.h"

#define restrict RESTRICTKEYWORD

Field::Field(Master &masterin, Grid &gridin)
{
  master = &masterin;
  grid = &gridin;

  data.resize(grid->getntot());

  master->printMessage("Constructed Field\n");
}

Field::~Field()
{
  master->printMessage("Destructed Field\n");
}

// overloaded operators
Field::Field(const Field &fieldin)
{
  master = fieldin.master;
  grid = fieldin.grid;

  data = fieldin.data;
}

namespace
{
  inline void copyvec(int * restrict out, int * restrict in, int size)
  {
    for(int i=0; i<size; ++i)
      out[i] = in[i];
  }
}

Field& Field::operator= (const Field &fieldin)
{
  // non-vectorized copy
  this->data = fieldin.data;

  // vectorized copy
  // copyvec((int*)data[0], (int*)&fieldin.data[0], data.size());

  return *this;
}

Field& Field::operator+=(const Field &fieldin)
{
  for(int i=0; i<this->data.size(); ++i)
    this->data[i] += fieldin.data[i];

  return *this;
}

namespace
{
  inline void addvecs(int * restrict out, int * restrict a, int * restrict b, int size)
  {
    for(int i=0; i<size; ++i)
      out[i] = a[i] + b[i];
  }
}

Field Field::operator+ (const Field &fieldin) const
{
  // copy the field
  Field fieldout(*this);

  // use non-vectorized addition
  // for(int i=0; i<data.size(); ++i)
  //   fieldout.data[i] = data[i] + fieldin.data[i];

  // use vectorized addition
  addvecs(&fieldout.data[0], (int*)&data[0], (int*)&fieldin.data[0], data.size());

  return fieldout;
}
