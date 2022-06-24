#pragma once
#include <vector>
#include <string>

typedef std::vector<std::vector<double>> vec2d;
typedef std::vector<std::vector<unsigned int>> vec2ui;
typedef std::vector<double> vec1d;
typedef std::vector<int> vec1i;


class face
{
    public:
    double xf,yf,S;
    double n[2], s[2];
    int owner_cell_index, neigbour_cell_index;
    face(vec1d const& a, vec1d const& b);
};

class cell
{
    public:
    double x = 0, y = 0, V;
    unsigned int cell_walls[4];

    cell();
    cell(vec1i nodes,vec2d const& all_nodes);
};

typedef std::vector<cell> cell_vec;
typedef std::vector<face> face_vec;

class mesh
{
    public:
    vec2d nodes;
    vec2ui edges,quads;
    cell_vec cells;
    face_vec walls;

    int quads_offset;
    vec1i ghost_cell_idx;
    vec1i ghost_cell_val;

    int N_cells, N_walls;
    
    mesh(std::string path);
    void load_mesh(std::string path, vec2d& nodes, vec2ui& edges, vec2ui& quads);
    void print_mesh();
    void sort_mesh();

    int find_neigbour_cell(vec1i common_nodes_idx,int owner_idx);
    bool wall_uniqueness(face const& new_wall);
    void construct_ghost_cells();
    void construct_cells();
};