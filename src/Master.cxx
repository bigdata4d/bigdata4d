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

#ifdef USEMPI
#include <mpi.h>
#endif

#include <iostream>
#include "Master.h"

#ifdef USEMPI
Master::Master()
{
  initialized = false;
  allocated = false;

  mpiid = 0;

  try
  {
    // initialize the MPI
    int n;
    n = MPI_Init(NULL, NULL);
    if(checkError(n))
    {
      printError("Error in Master constructor\n");
      throw 1;
    }

    initialized = true;

    // get the rank of the current process
    n = MPI_Comm_rank(MPI_COMM_WORLD, &mpiid);
    if(checkError(n))
    {
      printError("Error in Master constructor\n");
      throw 1;
    }

    // get the total number of processors
    n = MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(checkError(n))
    {
      printError("Error in Master constructor\n");
      throw 1;
    }

    char message[1024];
    std::sprintf(message, "Starting Master on %d process(es)\n", nprocs);
    printMessage(message);
  }

  catch (...)
  {
    cleanup();
    throw 1;
  }
}
#else
Master::Master()
{
  initialized = true;
  allocated = false;

  mpiid = 0;
  nprocs = 1;

  char message[1024];
  std::sprintf(message, "Starting Master on %d process(es)\n", nprocs);
  printMessage(message);
}
#endif

Master::~Master()
{
  cleanup();

  char message[1024];
  std::sprintf(message, "Finished Master on %d process(es)\n", nprocs);
  printMessage(message);
}

void Master::cleanup()
{
#ifdef USEMPI
  if(initialized)
    MPI_Finalize();
#endif
}

/*
int Master::init()
{
  int n;

  if(nprocs != npx*npy)
  {
    if(mpiid == 0) std::printf("ERROR nprocs = %d does not equal npx*npy = %d*%d\n", nprocs, npx, npy);
    return 1;
  }

  int dims    [2] = {npy, npx};
  int periodic[2] = {true, true};

  // define the dimensions of the 2-D grid layout
  n = MPI_Dims_create(nprocs, 2, dims);
  if(checkerror(n))
    return 1;

  // create a 2-D grid communicator that is optimized for grid to grid transfer
  // first, free our temporary copy of COMM_WORLD
  n = MPI_Comm_free(&commxy);
  if(checkerror(n))
    return 1;
  // for now, do not reorder processes, blizzard gives large performance loss
  n = MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periodic, false, &commxy);
  if(checkerror(n))
    return 1;
  n = MPI_Comm_rank(commxy, &mpiid);
  if(checkerror(n))
    return 1;

  // retrieve the x- and y-coordinates in the 2-D grid for each process
  int mpicoords[2];
  n = MPI_Cart_coords(commxy, mpiid, 2, mpicoords);
  if(checkerror(n))
    return 1;

  mpicoordx = mpicoords[1];
  mpicoordy = mpicoords[0];

  int dimx[2] = {false, true };
  int dimy[2] = {true , false};

  n = MPI_Cart_sub(commxy, dimx, &commx);
  if(checkerror(n))
    return 1;
  n = MPI_Cart_sub(commxy, dimy, &commy);
  if(checkerror(n))
    return 1;

  // find out who are the neighbors of this process to facilitate the communication routines
  n = MPI_Cart_shift(commxy, 1, 1, &nwest , &neast );
  if(checkerror(n))
    return 1;
  n = MPI_Cart_shift(commxy, 0, 1, &nsouth, &nnorth);
  if(checkerror(n))
    return 1;

  // create the requests arrays for the nonblocking sends
  int npmax;
  npmax = std::max(npx, npy);

  // have at least as many communicators as prognostic variables
  npmax = std::max(npmax, 8*4);
  reqs  = new MPI_Request[npmax*2];
  reqsn = 0;

  allocated = true;

  return 0;
}
*/

void Master::printMessage(std::string message)
{
  if(mpiid == 0)
    std::cout << message;
}

void Master::printError(std::string message)
{
  if(mpiid == 0)
    std::cerr << message;
}

int Master::checkError(int n)
{
#ifdef USEMPI
  char errbuffer[MPI_MAX_ERROR_STRING];
  int errlen;

  if(n != MPI_SUCCESS)
  {
    MPI_Error_string(n, errbuffer, &errlen);
    std::printf("ERROR MPI %s\n", errbuffer);
    return 1;
  }
#endif

  return 0;
}
