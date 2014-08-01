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

#include "Timer.h"
#include "Master.h"

Timer::Timer(Master &masterin)
  : master(masterin)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
  master.printMessage("Start timer\n");
  samples.push_back(master.getTime());
}

void Timer::end()
{
  samples.push_back(master.getTime());
  master.printMessage("End timer\n");
}

void Timer::sample()
{
  samples.push_back(master.getTime());
}

double Timer::getTotal()
{
  return samples.back() - samples.front();
}
