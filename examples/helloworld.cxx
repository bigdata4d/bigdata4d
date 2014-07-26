#include <iostream>
#include "Master.h"

int main(int argc, char *argv[])
{
  Master master;
  master.start(argc, argv);

  if(master.mpiid == 0)
    std::cout << "Hello world!\n";

  return 0;
}
