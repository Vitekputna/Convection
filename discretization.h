
inline double upwind(double phi, double owner, double neighbour)
{
    return std::max(0.0,phi)*owner + std::min(0.0,phi)*neighbour;
}