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

#ifndef MASTER
#define MASTER

#ifdef USEMPI
#include <mpi.h>
#endif

#include <string>

class Master
{
  public:
    static Master &getInstance();

    void printMessage(std::string);
    void printError  (std::string);

    double getTime();

    int mpiid;

  private:
    Master();
    ~Master();

    // \TODO CUDA does not allow yet delete
    Master(const Master &); //= delete;
    Master &operator=(const Master &); //= delete;

    void cleanup();
    int checkError(int);

    bool allocated;
    bool initialized;

    int nprocs;
};
#endif
