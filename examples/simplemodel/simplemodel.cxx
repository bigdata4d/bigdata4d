#include <iostream>
#include "Master.h"
#include "Simpleapp.h"

int main(int argc, char *argv[])
{
  try
  {
    Master master;
    Simpleapp application(&master, argc, argv);

    application.exec();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
