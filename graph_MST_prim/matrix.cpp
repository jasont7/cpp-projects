#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <cassert>
#include <cstdlib>
#include <string>
#include "matrix.hpp"

//#define DOTTY

const double INFINITY = std::numeric_limits<double>::infinity();

typedef std::vector<std::vector<double>> matrix_type;

void kill()
{
    std::cout << "We are terminating your program!!!!!" << std::endl;
    exit(10);
}

matrix_type Create_Matrix(const unsigned int size)
{
    // create a 2 dimensional vector of size X size
    // elements and set INFINITY as its default value
   std::vector <
       std::vector <double>
       > temp (size, std::vector<double> (size, INFINITY));
   return temp;
}

void Print_Matrix(const matrix_type &matrix, std::string message)
{
    if (matrix.size() == 0) {
        std::cout << message << " is empty." << std::endl;
        return;
    }

    std::cout << message << ". Size : "  << matrix.size() 
              << " x " << matrix.at(0).size() << std::endl;
    for (auto &x : matrix) {
        for (auto &y: x) {
            std::cout.width(3);
            if (y < INFINITY )
                std::cout <<  y << " : ";
            else 
                std::cout <<   " -  : ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Print_Dotty(const matrix_type &matrix, const matrix_type &adj)
{
    std::cout << "graph {\n\
         overlap=\"scalexy\"\n\
         splines=true \n\
         node [style=filled, color=greenyellow];\n\
         edge [penwidth=1.5];\n\
         sep = 1.2;\n\
         mclimit = 100;\n\
         start = 0\n\
" ;

    for (unsigned int i=0; i < matrix.size(); i++) {
        std::cout << char('A' + i) << "[label=\"" 
                  << char('A' + i) << "(" << i << ")\"]"
                  << std::endl;
    }
    for (unsigned int i=0; i < matrix.size(); i++) {
        auto &thisRow = matrix.at(i);
        for (unsigned int j = 0; j < thisRow.size();j++) {
            double d = thisRow.at(j);
            if (d < INFINITY && i < j) {
                std::cout <<  char('A' + i) << " -- " << char('A'+j) 
                          << "[label=\""  << matrix.at(i).at(j) << "\""
                          << ",weight="  << int(matrix.at(i).at(j)) 
                    ;
                if (adj.at(i).at(j) < INFINITY) {
                    std::cout << ",color=red,penwidth=3.0";
                }
                std::cout << "]" << std::endl;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
}

void Print_Adjacency(const matrix_type &matrix, std::string message)
{
    std::cout << message << ". Size : "  << matrix.size() << std::endl;
    
    for (unsigned int i=0; i < matrix.size(); i++) {
        std::cout << "From City: " << char('A' + i) << " -> ";

        auto &thisRow = matrix.at(i);
        for (unsigned int j = 0; j < thisRow.size();j++) {
            double d = thisRow.at(j);
            if (d < INFINITY ) {
                std::cout <<  "(" << char('A' + j) << "," << d << ") ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
}

matrix_type  Read_Matrix()
{
    unsigned int count {};
    unsigned int from {};
    unsigned int to {};
    double distance {};
    
    if (! (std::cin >> count)) {
        std::cout << "Nothing to read" << std::endl;
        kill();
    }
    
    matrix_type cities = Create_Matrix(count);

    while (std::cin >> from >> to >> distance) {

        if (from >= count) {
            std::cout << "From city is too large " << from << std::endl;
            kill();
        }
        if (to >= count) {
            std::cout << "Destination city is too large " << to << std::endl;
            kill();
        }

        cities.at(from).at(to) = distance;
        cities.at(to).at(from) = distance;
    }
    return cities;
}

void Print_Visited(std::set<int>& visited)
{
    std::cout <<"Visited: [";
    for(auto el: visited){
        std::cout << el << ",";
    }
    std::cout << "]"<< std::endl;
    std::cout << std::endl;
}

void Verify_Undirected_Matrix(matrix_type &m, std::string name)
{
    unsigned int size = m.size();
    for (unsigned int i=0; i < m.size(); i++) {

        auto &thisRow = m.at(i);

        if (thisRow.size() != size) {
            std::cout << "Error: Row " << i << " of matrix " << name
                      << " should be of size " << size << std::endl;
            Print_Matrix(m, name);
            kill();
        }
        for (unsigned int j = 0; j < thisRow.size();j++) {
            if (m.at(i).at(j) != m.at(j).at(i)) {
                std::cout << "Error: Matrix " << name << " should be symmetric"
                          << std::endl
                          << "Positions [" << i << "," << j << "] and " 
                          << " [" << j << "," << i << "] are different [" 
                          << m.at(i).at(j) << "][" << m.at(i).at(j) << "]"
                          << std::endl;
                Print_Matrix(m, name);
                kill();
            }
        }            
    }
}

void Verify_Subgraph(matrix_type graph, matrix_type subgraph)
{
    
    // verify size
    //verify is a matrix
    
    if (graph.size() != subgraph.size()) {
        std::cout << "Error: The original graph and the minimum spanning tree have different sizes"
                  <<std::endl;
        Print_Matrix(graph, "Original graph");
        Print_Matrix(subgraph, "Minimum Spanning Tree");
        kill();
    }

    Verify_Undirected_Matrix(graph, "Original graph");
    Verify_Undirected_Matrix(subgraph, "Minimum Spanning Tree");

    // Verify one is a subgraph of the other
    unsigned int size = graph.size();
    for (unsigned int i=0; i < size; i++) {
        for (unsigned int j=0; j < size; j++) {
            if (subgraph.at(i).at(j) != INFINITY && 
                subgraph.at(i).at(j) != graph.at(i).at(j)) {
                std::cout << "Error: the Minimum Spanning Tree  should be a subgraph of the original graph"
                          << std::endl
                          << "Positions [" << i << "," << j << "] are different "  <<std::endl
                          << "Original graph [" << graph.at(i).at(j)
                          << "] subgraph [" << subgraph.at(i).at(j) << "]"
                          << std::endl;
                kill();
            }
        }
    }

    
}





