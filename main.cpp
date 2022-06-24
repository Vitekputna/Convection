#include <iostream>
#include "mesh.h"

int main(int argc, char** argv)
{
    mesh MSH("block.mesh");
    //MSH.print_mesh();
    //std::cout << MSH.find_neigbour_cell(std::vector<int>{8,9},3) << "\n";

    std::cout << MSH.walls.size() << "\n";

    for(auto const& quad : MSH.quads)
    {
        std::cout << quad[0] << " " << quad[1] << " "<< quad[2] << " "<< quad[3] << "\n";
    }
    int i = 0;
    for(auto const& ghost : MSH.ghost_cell_idx)
    {
        std::cout << MSH.quads[ghost][0] << " "<< MSH.quads[ghost][1] << " " << MSH.ghost_cell_val[ghost-MSH.quads_offset] << "\n";
        i++;
    }

    return 0;
}