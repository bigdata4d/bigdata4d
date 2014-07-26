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

#ifndef MASTER
#define MASTER

#ifdef USEMPI
#include <mpi.h>
#endif

#include <string>

class Master
{
  public:
    Master();
    ~Master();

    // disable the assignment and copy constructors
    Master(const Master &) = delete;
    Master &operator=(const Master &) = delete;

    // int init();
    void printMessage(std::string);
    void printError  (std::string);

    int mpiid;

  private:
    void cleanup();
    int checkError(int);

    bool allocated;
    bool initialized;

    int nprocs;
};
#endif
