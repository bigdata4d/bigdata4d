#include <iostream>
#include "Master.h"
#include "Application.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master(argc, argv);
    Application application(&master);

    application.exec();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
