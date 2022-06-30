#include <iostream>
#include "mesh.h"

int main(int argc, char** argv)
{
    double dt = 0.05;
    double flux;
    uint nt = 1000;

    mesh MSH(argv[1]); 
    std::cout << MSH.N << "\n";

    double U[MSH.N];

    for(unsigned int i = 0; i < MSH.N; i++)
    {
        if(MSH.cells[i].x > 1 && MSH.cells[i].x < 2 && MSH.cells[i].y > 1 && MSH.cells[i].y < 2)
        {
            U[i] = 1;
        }
        else
        {
            U[i] = 0;
        }
    }

    int w = 0;
    for(unsigned int t = 0; t < nt; t++)
    {
        for(auto const& wall : MSH.walls)
        {
            flux = (U[wall.neigbour_cell_index] - U[wall.owner_cell_index])*dt*wall.S;
            U[wall.owner_cell_index] += flux;
            U[wall.neigbour_cell_index] -= flux;
            //std::cout << w << " " << flux << "\n";
            //w++;
        }
    }
    
    for(uint i = 0; i < MSH.N; i++)
    {
        std::cout << MSH.cells[i].x << " " << MSH.cells[i].y << " " << U[i] << "\n";
    }

    return 0;
}