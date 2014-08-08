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
    // auto grid = createGrid<double>(master, 100, 100, 100, 3);
    Grid<double> grid = createGrid<double>(master, 100, 100, 100, 3);

    Field<double,double> a  = createField<double>(master, grid, "a");
    Field<double,double> at = createField<double>(master, grid, "a");

    a.randomize(10);

    Diffusion<double,double> diff(master, grid);

    Timer timer(master, "Diffusion (CPU)");
    timer.start();
    for(int n=0; n<500; ++n)
      diff.exec(at, a);
    timer.end();

    DiffusionGPU<double,double> diffGPU(master, grid);

    thrust::device_vector<double> a_gpu (a .data.begin(), a .data.end());
    thrust::device_vector<double> at_gpu(at.data.begin(), at.data.end());

    Timer timer2(master, "Diffusion (GPU)");
    timer2.start();
    for(int n=0; n<500; ++n)
      diffGPU.exec(at_gpu, a_gpu);
    timer2.end();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
