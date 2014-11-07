#include <iostream>
#include "Master.h"

int main(int argc, char *argv[])
{
  try
  {
    Master &master = Master::getInstance();
    master.printMessage("Hello World!\n");
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
