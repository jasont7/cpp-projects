#ifndef __MATRIX_HPP
#define __MATRIX_HPP

#include <vector>

#ifdef INFINITY
#undef INFINITY
#endif

extern const double INFINITY;

typedef std::vector<std::vector<double>> matrix_type;


// terminates program with an error message
void kill();

// creates a matrix of given size
//
// parameter:
//
//    size: size of the square matrix to create
//
// returns:
//    a matrix_type of give size with values initialized to INFINITY
// 
matrix_type Create_Matrix(const unsigned int size);

// print a matrix in matrix form
//
// parameters:
//
//     matrix: matrix to print
//     message: message to print before the matrix
//
void Print_Matrix(const matrix_type &matrix, std::string message);

// print a matrix as an adjacency list
//
// parameters:
//
//     matrix: matrix to print
//     message: message to print before the matrix
//
void Print_Adjacency(const matrix_type &matrix, std::string message);


// verify that the second parameter is a subgraph of the first
// if it is not, terminates the program
//
//   a subgraph should have the same dimensions as the original
//   graph and if there is an edge in the subgraph it
//   should exist in the graph
// 
// parameters:
//    graph: a matrix representing a graph
//    subgraph: a matrix representing a graph
//
void Verify_Subgraph(matrix_type graph, matrix_type subgraph);


// read a matrix from standard input
//
// returns:
//     a square matrix with the corresponding data
//
matrix_type  Read_Matrix();

// see minimum.cpp
matrix_type Minimum_Spanning_Tree(const matrix_type & matrix);

// see minimum.cpp
double Calculate_Cost(const matrix_type &matrix);



#endif 
