#include <iostream>
#include "Master.h"
#include "Application.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Application application(&master, argc, argv);

    application.exec();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
