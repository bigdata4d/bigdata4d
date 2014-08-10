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
    Master master;
    try
    {
      Grid<double> grid = createGrid<double>(master, 128, 128, 512, 3);

      Field<double,double> a  = createField<double>(master, grid, "a" );
      Field<double,double> at = createField<double>(master, grid, "at");

      a.randomize(10);

      Diffusion<double,double> diff(master, grid);

      Timer timer1(master, "Diffusion (CPU)");
      timer1.start();
      for(int n=0; n<100; ++n)
        diff.exec(at, a);
      timer1.end();

      DiffusionGPU<double,double> diffGPU(master, grid);

      thrust::device_vector<double> a_gpu (a.data.begin(), a.data.end());
      thrust::device_vector<double> at_gpu(a.data.size());

      Timer timer2(master, "Diffusion (GPU)");
      timer2.start();
      for(int n=0; n<100; ++n)
        diffGPU.exec(at_gpu, a_gpu);
      // wait until all calculations are done
      cudaDeviceSynchronize();
      timer2.end();

      Field<double, double> at_cuda = createField<double>(master, grid, "at_cuda");
      thrust::copy(at_gpu.begin(), at_gpu.end(), at_cuda.data.begin());

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
