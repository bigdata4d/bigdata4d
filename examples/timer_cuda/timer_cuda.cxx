#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Timer.h"

// CUDA functions
extern void prepareCUDA(float **, float **, float *, float *);
extern void testCUDA(float *, float *);
extern void waitCUDA();
extern void finishCUDA(float *, float *, float *);

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Grid grid(master, 384, 384, 384);

    Field<float> a(master, grid, "a");

    // fill field with random numbers
    for(auto &i : a.data)
      i = std::rand() % 10;

    // make a copy of a
    Field<float> b(a);

    Timer timer1(master);
    timer1.start();
    for(int n=0; n<100; ++n)
      a += b;
    timer1.end();

    float *a_gpu, *b_gpu;
    prepareCUDA(&a_gpu, &b_gpu, &b.data[0], &b.data[0]);

    Timer timer2(master);
    timer2.start();
    for(int n=0; n<100; ++n)
      testCUDA(a_gpu, b_gpu);
    waitCUDA();
    timer2.end();

    std::ostringstream message;
    message << "Elapsed time (s): "
            << std::setprecision(5) << timer1.getTotal() << ", "
            << std::setprecision(5) << timer2.getTotal() << "\n"
            << "Speedup: " << timer1.getTotal() / timer2.getTotal() << "\n";
    master.printMessage(message.str());

    Field<float> acuda(master, grid, "acuda");

    finishCUDA(a_gpu, b_gpu, &acuda.data[0]);

    for(int n=3; n<a.data.size(); n+=384*384*20)
    {
      std::ostringstream message;
      message << std::setw(8);
      message << n << " = {" 
        << std::setw(6) <<     a.data[n] << ", "
        << std::setw(6) << acuda.data[n] << " }\n";
      master.printMessage(message.str());
    }
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
