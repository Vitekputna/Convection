#include <iostream>
#include "mesh.h"

int main(int argc, char** argv)
{
    mesh MSH(argv[1]);
    MSH.export_mesh();
    return 0;
}