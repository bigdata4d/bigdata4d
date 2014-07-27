/*
 * BigData4D
 * Copyright (c) 2014 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigData4D are derived from
 * MicroHH (https://github.com/MicroHH)
 *
 * This file is part of BigData4D
 *
 * BigData4D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * BigData4D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with BigData4D.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SimpleApplication.h"
#include "Master.h"

SimpleApplication::SimpleApplication(Master *masterin, int argc, char *argv[]) : Application(masterin, argc, argv)
{
  /*
  // process the command line options
  name = "default";
  if(argc <= 1)
  {
    if(mpiid == 0) std::printf("No command line options\n");
    mode = "default";
  }
  else
  {
    // check the execution mode
    mode = argv[1];

    if(argc > 2)
      name = argv[2];
  }
  if(mpiid == 0) std::printf("Mode = %s, Name = %s\n", mode.c_str(), name.c_str());
  */

  master->printMessage("Started application SimpleApplication\n");
}

SimpleApplication::~SimpleApplication()
{
  master->printMessage("Finished application SimpleApplication\n");
}

void SimpleApplication::exec()
{
  master->printMessage("Hello world!\n");
}
