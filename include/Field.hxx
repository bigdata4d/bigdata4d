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
#include "Field.h"
#include "Master.h"
#include "Grid.h"

#define restrict RESTRICTKEYWORD

template<class T, class TG>
Field<T,TG>::Field(Master &masterin, Grid<TG> &gridin, const std::string namein)
  : master(masterin),
    grid(gridin)
{
  name = namein;

  try
  {
    data.resize(grid.getntot());
  }
  catch (...)
  {
    master.printError("Bad allocation\n");
    throw 1;
  }

  std::ostringstream message;
  message << "Constructing Field " << name << "\n";
  master.printMessage(message.str());
}

template<class T, class TG>
Field<T,TG>::~Field()
{
  std::ostringstream message;
  message << "Destructed Field " << name << "\n";
  master.printMessage(message.str());
}

// overloaded operators
template<class T, class TG>
Field<T,TG>::Field(const Field &fieldin)
  : master(fieldin.master),
    grid(fieldin.grid)
{
  name = "copy of " + fieldin.name;

  data = fieldin.data;

  std::ostringstream message;
  message << "Constructing Field " << name << "\n";
  master.printMessage(message.str());
}

namespace
{
  template<typename T>
  inline void copyvec(T * const restrict out, const T * const restrict in, const int size)
  {
    for(int i=0; i<size; ++i)
      out[i] = in[i];
  }
}

template<class T, class TG>
Field<T,TG>& Field<T,TG>::operator= (const Field &fieldin)
{
  // non-vectorized copy
  // this->data = fieldin.data;

  // vectorized copy
  copyvec(&data[0], &fieldin.data[0], data.size());

  return *this;
}

namespace
{
  template<typename T>
  inline void copyaddvec(T * const restrict out, const T * const restrict in, const int size)
  {
    for(int i=0; i<size; ++i)
      out[i] += in[i];
  }
}

template<class T, class TG>
Field<T,TG>& Field<T,TG>::operator+=(const Field &fieldin)
{
  // for(int i=0; i<this->data.size(); ++i)
  //   this->data[i] += fieldin.data[i];

  copyaddvec(&data[0], &fieldin.data[0], data.size());

  return *this;
}

namespace
{
  template<typename T>
  inline void addvecs(T * const restrict out, const T * const restrict a, const T * const restrict b, int size)
  {
    for(int i=0; i<size; ++i)
      out[i] = a[i] + b[i];
  }
}

template<class T, class TG>
Field<T,TG> Field<T,TG>::operator+ (const Field<T,TG> &fieldin) const
{
  // copy the field
  Field<T,TG> fieldout(*this);

  // use non-vectorized addition
  // for(int i=0; i<data.size(); ++i)
  //   fieldout.data[i] = data[i] + fieldin.data[i];

  // use vectorized addition
  addvecs(&fieldout.data[0], &data[0], &fieldin.data[0], data.size());

  return fieldout;
}
