#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "matrix.hpp"

struct connection {
    unsigned int origin;
    unsigned int destination;
    double weight;
};

std::vector<connection> Connections(const matrix_type& G, const std::vector<unsigned int>& V) {
    std::vector<connection> connections {};
    for (auto vertex : V) {
        unsigned int dest {0};
        for (auto weight : G.at(vertex)) {
            if (std::find(V.begin(), V.end(), dest) == V.end() && weight != INFINITY) { // Destination not yet in V
                connection conn {vertex, dest, weight};
                connections.push_back(conn);
            }
            dest++;
        }
    }
    return connections;
}

// Compute minimum spanning tree of a graph
//
// Parameters:
//      G: input graph (represented by an adjacency matrix)
//
// Result:
//      a matrix representing the minimum spanning tree of G
//
matrix_type Minimum_Spanning_Tree(const matrix_type& G) {
	unsigned int N = G.size();
    matrix_type result = Create_Matrix(N);

    std::vector<unsigned int> visited {0}; // Initially contains the first vertex
    std::vector<connection> connPool = Connections(G, visited); // Contains all possible connections
    while (visited.size() < N) {
        connection minWeightConn {};
        minWeightConn.weight = INFINITY;
        for (auto conn : connPool) { // Find the minimum-weight connection
            if (conn.weight < minWeightConn.weight) {
                minWeightConn = conn;
            }
        }
        visited.push_back(minWeightConn.destination); // Add new vertex to visited
        result.at(minWeightConn.origin).at(minWeightConn.destination) = minWeightConn.weight; // Update result matrix
        result.at(minWeightConn.destination).at(minWeightConn.origin) = minWeightConn.weight;
        connPool = Connections(G, visited); // Update possible connections pool
    }

    return result;
}

// Calculate the overall cost of a graph
//
// Parameters:
//      G: input graph (represented by an adjacency matrix)
//
// Result:
//      the total sum of the costs of the edges in the graph
//
double Calculate_Cost(const matrix_type& G) {
    double sumCost {0};
    for (size_t i=0; i < G.size(); i++) {
        for (size_t j=0; j < i; j++) {
            if (G.at(i).at(j) != INFINITY)
                sumCost += G.at(i).at(j);
        }
    }
    return sumCost;
}

