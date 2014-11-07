#include <iostream>
#include "Master.h"
#include "SimpleApplication.h"

int main(int argc, char *argv[])
{
  try
  {
    SimpleApplication application(argc, argv);
    application.exec();
  }

  catch (...)
  {
    return 1;
  }

  return 0;
}
