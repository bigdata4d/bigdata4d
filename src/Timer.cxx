/*
 * BigDataGrid
 * Copyright (c) 2014-2015 Chiel van Heerwaarden
 *
 * Many of the classes and functions in BigDataGrid are derived from
 * MicroHH (https://github.com/MicroHH)
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

#include <sstream>
#include <iomanip>
#include "Timer.h"
#include "Master.h"

Timer::Timer(std::string namein)
{
  name = namein;
}

Timer::~Timer()
{
}

void Timer::start()
{
  Master &master = Master::getInstance();
  std::ostringstream message;
  message << "Start timer " << name << "\n";
  master.printMessage(message.str());
  samples.push_back(master.getTime());
}

void Timer::end()
{
  Master &master = Master::getInstance();
  samples.push_back(master.getTime());
  std::ostringstream message;
  message << "End timer " << name << ", elapsed time (s): "
          << std::setprecision(5) << getTotal() << "\n";
  master.printMessage(message.str());
}

void Timer::sample()
{
  Master &master = Master::getInstance();
  samples.push_back(master.getTime());
}

double Timer::getTotal()
{
  Master &master = Master::getInstance();
  return samples.back() - samples.front();
}
