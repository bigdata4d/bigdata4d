#include <iostream>
#include "Master.h"
#include "SimpleApplication.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    SimpleApplication application(&master, argc, argv);

    application.exec();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
