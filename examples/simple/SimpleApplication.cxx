/*
 * BigDataGrid
 * Copyright (c) 2014-2015 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigDataGrid are derived from
 * MicroHH (https://github.com/microhh)
 *
 * This file is part of BigDataGrid
 *
 * BigDataGrid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * BigDataGrid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with BigDataGrid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SimpleApplication.h"
#include "Master.h"

SimpleApplication::SimpleApplication(int argc, char *argv[])
  : Application(argc, argv)
{
  Master &master = Master::getInstance();
  master.printMessage("Started application SimpleApplication\n");
}

SimpleApplication::~SimpleApplication()
{
  Master &master = Master::getInstance();
  master.printMessage("Finished application SimpleApplication\n");
}

void SimpleApplication::exec()
{
  Master &master = Master::getInstance();
  master.printMessage("Hello world!\n");
}
