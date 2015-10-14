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

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include "Master.h"
#include "Grid.h"
#include "Field.h"
#include "Diffusion.h"
#include "Timer.h"

int main(int argc, char *argv[])
{
    try
    {
        const int iter = 100;
        Grid<double> grid = createGrid<double>(128, 128, 128, 3);

        Field<double,double> a   = createField<double>(grid, "a"  );
        Field<double,double> at  = createField<double>(grid, "at" );
        Field<double,double> at2 = createField<double>(grid, "at2");

        a.randomize(10);

        Diffusion<double,double> diff(grid);

        Timer timer1("Diffusion (CPU), not threaded");
        timer1.start();
        for (int n=0; n<iter; ++n)
            diff.exec(at, a, false);
        timer1.end();

        Timer timer2("Diffusion (CPU), threaded");
        timer2.start();
        for (int n=0; n<iter; ++n)
            diff.exec(at2, a, true);
        timer2.end();

        // Check for identical results
        bool identical = true;
        const GridDims dims = grid.getDims();
        for (long k=dims.kstart; k<dims.kend; ++k)
            for (long j=dims.jstart; j<dims.jend; ++j)
                for (long i=dims.istart; i<dims.iend; ++i)
                    if (at(i,j,k) != at2(i,j,k))
                        identical = false;

        if (!identical)
            throw std::runtime_error("Threaded version does not return identical field!");
    }

    catch (std::exception &e)
    {
        std::ostringstream message;
        message << "Exited with exception: " << e.what() << "\n";
        Master &master = Master::getInstance();
        master.printMessage(message.str());
        return 1;
    }

    return 0;
}
