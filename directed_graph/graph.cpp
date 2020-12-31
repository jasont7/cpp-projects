#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <cmath>
#include <climits>
#include <sstream>
#include <unordered_set>  
#include <algorithm>
#include <fstream>
#include <ios>

#include "graph.hpp"

void Try_Some_Operations(directed_graph &g)
{
    std::cout << std::endl
              << "Try some of the complex operations "
              << std::endl << std::endl;;

    auto t = g.transpose();

    auto i = g.complement();

    t.print("Transposed");
    auto t2 = t.transpose();
    t2.print("transposed of transposed: equal to original");
    i.print("Inverted");
}

void Remove_Half_Nodes(directed_graph &g)
{
    if (g.is_empty()) {
        return;
    }
    auto ver = g.vertices();

    std::cout << "Testing subgraph ... keeping" << std::endl;

    // convert set to vector
    std::vector<int> vec (ver.begin(), ver.end());

    // create a subset with half of the nodes
    std::set<int> subVer(vec.begin(), vec.begin() + vec.size()/2);
        for(auto el: subVer) {
        std::cout << " vertex "<< el << std::endl;
    }
    
    auto s = g.subgraph(subVer);

    s.print("Result subraph");


}

void Do_Reachability(directed_graph &g)
{
    std::cout << std::endl;
    g.print("Try reachability of all vertices in g. First print graph: ");
    std::cout << std::endl;
    auto ver = g.vertices();
    for (int v1: ver) {
        for (int v2: ver) {
            std::cout << "edge " << v1 << " " << v2 << std::boolalpha << " "<< g.is_reachable(v1,v2) << std::endl;
        }
    }
}

void Print_By_Successor(directed_graph &g)
{
    std::cout << "Print the graph using using vertices and successors" << std::endl;

    for (int v1: g.vertices()) {
        for (int v2: g.successors(v1)) {
            std::cout << "Edge [" << v1 << "] -> [" << v2 << "] weight [" << g.weight(v1,v2) << "]" << std::endl;
        }
    }
}

void Print_By_Predecessor(directed_graph &g)
{

    std::cout << "Print the graph again using vertices and predecessors. Output is ordered by destination vertex" << std::endl;

    for (int v1: g.vertices()) {
        for (int v2: g.predecessors(v1)) {
            std::cout << "Edge [" << v2 << "] -> [" << v1 << "] weight [" << g.weight(v2,v1) << "]" << std::endl;
        }
    }
}

directed_graph Read_Graph(std::string inputFile)
{
    directed_graph g;
    int from;
    int to;
    double weight;
    int min = INT_MAX;
    int max = -1;

    std::ifstream input;
    input.open(inputFile, std::ios::in);
    if (!input.is_open()) {
        std::cerr << "Unable to open test file ["<< inputFile << "]" << std::endl;
        exit(1);
    }

    std::cout << "Reading edges " << std::endl;
    while (input >> from >> to >> weight) {
        std::cout << from << " " << to <<  " " << weight << std::endl;;
        g.add_edge(from, to, weight);
        if (from < min) {
            min = from;
        }
        if (from > max) {
            max = from;
        }
    } 
    // try a values I know are not there
    try {
        g.weight(max+1,1); // should generate an error
    } catch (const std::exception& e) {
        std::ostringstream outs;
        outs << "Expected exception :" << max+1 << "->" << 1 << " ";
        std::cout << outs.str() << e.what() << std::endl;
    }    
    try {
        g.weight(min-1,1); // should generate an error
    } catch (const std::exception& e){
        std::ostringstream outs;
        outs << "Expected exception :" << min-1 << "->" << 1 << " ";
        std::cout << outs.str() << e.what() << std::endl;
    }    
    return g;
}

void Test_From_File(std::string fileName)
{

    auto g = Read_Graph(fileName);

    g.print();
    Print_By_Successor(g);
    Print_By_Predecessor(g);
    Try_Some_Operations(g);
    Remove_Half_Nodes(g);
    Do_Reachability(g);
}


void Test_Simple()
{
    directed_graph a;
    a.add_edge(2,3);
    a.print("Graph with default constructor and Default add edge");

    directed_graph g(0);

    std::cout << "Insert some nodes into the graph" << std::endl;

    g.add_edge(1,2,5.0);
    g.add_edge(1,7,3.0);
    g.add_edge(2,3);
    g.add_edge(2,3,4.1);
    g.add_edge(2,4);
    g.add_edge(4,2,-1.4);
    g.add_edge(4,4,2.1);
    g.add_edge(7,2,3.4);
    g.add_edge(4,9,-1.1);

    g.print("Graph");

    std::cout << "Verify some weights" << std::endl;

    assert(g.weight(4,9) == -1.1);
    assert(g.weight(4,2) == -1.4);
    assert(g.weight(1,7) == 3.0);

    std::cout << "Force some throws" << std::endl;

    try {
        g.weight(4,5);
    } catch (const std::exception& e) {
        std::cout << "Expected exception " << e.what() << std::endl;
    }

    std::cout << "Make sure we can remove some nodes" << std::endl;

    assert(g.remove_edge(4,9)); // this one exist
    assert(g.remove_edge(4,3) == false); // this one does not exist

    g.print("Graph after removal");

    Print_By_Successor(g);
    Print_By_Predecessor(g);
    
    Try_Some_Operations(g);

    auto s = g.subgraph({1,2,3,5});
    s.print("Compute subgraph that includes only edges 1 2 3 and 5 (5 is not part of g)");

    auto s2 = g.subgraph({});
    s2.print("Subgraph empty");

    Do_Reachability(g);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        Test_Simple();
    } else {
        // silence warning
        Test_From_File(argv[1]);
    }
    return 0; 
}
