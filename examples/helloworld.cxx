#include <iostream>
#include "Master.h"

int main(int argc, char *argv[])
{
  Master master;
  master.start(argc, argv);

  master.printMessage("Hello World!\n");

  return 0;
}
