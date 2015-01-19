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

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Diffusion.h"
#include "DiffusionGPU.h"
#include "Timer.h"

int main(int argc, char *argv[])
{
  try
  {
    try
    {
      Grid<double> grid = createGrid<double>(128, 128, 512, 3);

      Field<double,double> a  = createField<double>(grid, "a" );
      Field<double,double> at = createField<double>(grid, "at");

      a.randomize(10);

      Diffusion<double,double> diff(grid);

      Timer timer1("Diffusion (CPU)");
      timer1.start();
      for(int n=0; n<100; ++n)
        diff.exec(at, a);
      timer1.end();

      DiffusionGPU<double,double> diffGPU(grid);

      thrust::device_vector<double> a_gpu (a.data.begin(), a.data.end());
      thrust::device_vector<double> at_gpu(a.data.size());

      Timer timer2("Diffusion (GPU)");
      timer2.start();
      for(int n=0; n<100; ++n)
        diffGPU.exec(at_gpu, a_gpu);
      // wait until all calculations are done
      cudaDeviceSynchronize();
      timer2.end();

      Field<double, double> at_cuda = createField<double>(grid, "at_cuda");
      thrust::copy(at_gpu.begin(), at_gpu.end(), at_cuda.data.begin());

      Master &master = Master::getInstance();
      std::ostringstream message;
      message << "Elapsed time (s): "
              << std::fixed << std::setprecision(5) << timer1.getTotal() << ", "
              << std::fixed << std::setprecision(5) << timer2.getTotal() << ", "
              << "Speedup CUDA: " << timer1.getTotal() / timer2.getTotal() << "\n";
      master.printMessage(message.str());

      // print some output
      const GridDims dims = grid.getDims();
      for(long k=dims.kstart+3; k<dims.kend; k+=dims.ktot/2)
        for(long j=dims.jstart+3; j<dims.jend; j+=dims.jtot/2)
          for(long i=dims.istart+3; i<dims.iend; i+=dims.itot/2)
          {
            long ijk = i + j*dims.icells + k*dims.ijcells;
            std::ostringstream message;
            message << "(" 
                    << std::setw(5) << i-dims.istart <<  "," 
                    << std::setw(5) << j-dims.jstart <<  "," 
                    << std::setw(5) << k-dims.kstart << ") = " 
                    << std::setw(10) << std::fixed << std::setprecision(3) << at.data[ijk] << ", "
                    << std::setw(10) << std::fixed << std::setprecision(3) << at_cuda.data[ijk] << "\n";
            master.printMessage(message.str());
          }
    }

    catch (std::exception &e)
    {
      std::ostringstream message;
      message << "Exception: " << e.what() << "\n";
      Master &master = Master::getInstance();
      master.printMessage(message.str());
      throw 1;
    }
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
