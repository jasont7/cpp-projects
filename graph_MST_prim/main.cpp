#include <iostream>
#include "matrix.hpp"


int main()
{
    matrix_type cities {};
    matrix_type mst {};

    cities = Read_Matrix();

    Print_Matrix(cities, "Input matrix");
    Print_Adjacency(cities, "Input Adjacency list");

    mst = Minimum_Spanning_Tree(cities);
    
    Verify_Subgraph(cities, mst);

    Print_Adjacency(mst, "Minimum Spanning Tree");

    double originalCost {Calculate_Cost(cities)};
    double mstCost      {Calculate_Cost(mst)};
    std::cout << "Cost of original matrix: " << originalCost << std::endl;
    std::cout << "Cost of minimum spanning tree: " << mstCost << std::endl;

    return 0;
}

