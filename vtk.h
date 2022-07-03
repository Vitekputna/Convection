#include <string>
#include <fstream>
#include "mesh.h"

void export_vtk(double *U, mesh msh, std::string name)
{
    std::ofstream f(name);

    f << "# vtk DataFile Version 2.0" << std::endl;
	f << "Unstructured Grid Example" << std::endl;
	f << "ASCII" << std::endl;
	f << "DATASET UNSTRUCTURED_GRID" << std::endl;
	f << std::endl;
	f << "POINTS" << " " << msh.nodes.size() << " " << "float" << std::endl;

    for (unsigned int i = 0; i < msh.nodes.size(); i++)
	{
		for (unsigned int j = 0; j < msh.nodes[0].size()-1; j++)
		{
			f << msh.nodes[i][j] << " ";
		}
		f << std::endl;
	}

    f << std::endl;
	f << "CELLS " << msh.N_cells << " " << (msh.N_cells) * 5 << std::endl;

    for(uint i = 0; i < msh.N_cells; i++)
    {
        f << 4 << " ";
        f << msh.quads[i][0] << " ";
        f << msh.quads[i][1] << " ";
        f << msh.quads[i][2] << " "; 
        f << msh.quads[i][3] << "\n";
    }

    f << std::endl;
	f << "CELL_TYPES " << msh.N_cells << std::endl;
	for (unsigned int i = 0; i < msh.N_cells; i++)
	{
		f << "9" << std::endl;
	}
	f << std::endl;

    f << "CELL_DATA " << msh.N_cells << std::endl;
	f << "SCALARS " << "u" << " float 1" << std::endl;
	f << "LOOKUP_TABLE default" << std::endl;
	for(uint i = 0; i < msh.N_cells; i++)
    {
        f << U[i] << "\n";
    }
	f << std::endl;
}