#include <iostream>
#include "mesh.h"
#include "discretization.h"
#include "vtk.h"
#include <math.h>

int main(int argc, char** argv)
{
    double dt = 0.001;
    double mi = 0.5;
    uint nt = std::stoi(argv[2]);

    mesh MSH(argv[1]); 
    std::cout << MSH.N << "\n";

    double U[MSH.N];
    double wall_flux[MSH.N_walls];

    //PP
    for(unsigned int i = 0; i < MSH.N; i++)
    {
        if(MSH.cells[i].x > 0.2 && MSH.cells[i].x < 0.4 && MSH.cells[i].y > 0.2 && MSH.cells[i].y < 0.4)
        {
            U[i] = 1;
        }
        else
        {
            U[i] = 0;
        }
    }

    
    int neighbour_idx, owner_idx;
    double dx;
    uint t;

    for(t = 0; t < nt; t++)
    {
        export_vtk(U,MSH,"out/test_" + std::to_string(t) + ".vtk");

        // wall flux
        for(uint w = 0; w < MSH.N_walls; w++)
        {
            neighbour_idx = MSH.walls[w].neigbour_cell_index;
            owner_idx = MSH.walls[w].owner_cell_index;
            //dx = sqrt( pow(MSH.cells[neighbour_idx].x - MSH.cells[owner_idx].x,2) 
            //    + pow(MSH.cells[neighbour_idx].y - MSH.cells[owner_idx].y,2) );
            //wall_flux[w] = (U[neighbour_idx] - U[owner_idx])/dx*MSH.walls[w].S;

            wall_flux[w] = upwind((MSH.walls[w].n[0] + MSH.walls[w].n[1])*MSH.walls[w].S,
                                  U[owner_idx],U[neighbour_idx]);
        }

        // apply wall fluxes to cells
        for(uint c = 0; c < MSH.N_cells; c++)
        {
            int w = 0;
            for(auto const& wall : MSH.cells[c].cell_walls)
            {
                //U[c] += mi*MSH.cells[c].owner_idx[w]*dt/MSH.cells[c].V*wall_flux[wall];
                U[c] -= MSH.cells[c].owner_idx[w]*dt/MSH.cells[c].V*wall_flux[wall];
                w++;
            }
        }

        // apply boundary
        for(uint i = MSH.quads_offset; i < MSH.N; i++)
        {
            U[i] = U[MSH.walls[MSH.cells[i].cell_walls[0]].owner_cell_index];
        }
    }
    export_vtk(U,MSH,"out/test_" + std::to_string(t) + ".vtk");
    

    return 0;
}