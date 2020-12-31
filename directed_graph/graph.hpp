#ifndef __GRAPH_HPP__
#define __GRAPH_HPP__

#include <set>
#include <map>
#include <list>
#include <vector>
#include <cmath>


class directed_graph {
private:
    std::vector<std::vector<double>> G {101, std::vector<double> (101, std::nan("")) };
    std::set<std::pair<int, int>> E {};
    double defaultWeight {};
public:
    directed_graph() {
        defaultWeight = -1;
    }
    directed_graph(double defaultEdgeWeight) {
        defaultWeight = defaultEdgeWeight;
    }

    bool is_empty() {
        return E.empty();
    }

    void add_edge(const int from, const int to) {
        G.at(from).at(to) = defaultWeight;
        std::pair<int, int> pair {from, to};
        E.insert(pair);
    }

    void add_edge(const int from, const int to, const double weight) {
        G.at(from).at(to) = weight;
        std::pair<int, int> pair {from, to};
        E.insert(pair);
    }

    std::set<std::pair<int, int>> edges() {
        return E;
    }
    bool edge_exists(const int from, const int to) {
        std::pair<int, int> p {from, to};
        return E.find(p) != E.end();
    }

    std::set<int> vertices() {
        std::set<int> V {};
        for (const auto& pair : E) {
            V.insert(pair.first);
            V.insert(pair.second);
        }
        return V;
    }
    bool vertex_exists(const int vertex) {
        std::set<int> V {vertices()};
        return V.find(vertex) != V.end();
    }

    bool remove_edge(const int from, const int to) {
        std::pair<int, int> pair {from, to};
        if (E.find(pair) != E.end()) {
            E.erase(pair);
            G.at(from).at(to) = std::nan("");
            return true;
        }
        return false;
    }

    bool remove_vertex(const int vertex) {
        if (vertex_exists(vertex)) {
            for (auto w : G.at(vertex))
                G.at(vertex).at(w) = std::nan("");

            for (const auto& pair : E) {
                if (pair.first == vertex || pair.second == vertex)
                    E.erase(pair);
            }
            return true;
        }
        return false;
    }

    double weight(const int from, const int to) {
        if (edge_exists(from, to))
            return G.at(from).at(to);
        else
            throw std::runtime_error("edge does not exist");
    }

    std::set<int> predecessors(int vertex) {
        if (vertex_exists(vertex)) {
            std::set<int> pSet {};
            for (const auto &pair : E) {
                if (pair.second == vertex)
                    pSet.insert(pair.first);
            }
            return pSet;
        } else return {};
    }

    std::set<int> successors(int vertex) {
        if (vertex_exists(vertex)) {
            std::set<int> sSet {};
            for (const auto &pair : E) {
                if (pair.first == vertex)
                    sSet.insert(pair.second);
            }
            return sSet;
        } else return {};
    }

    directed_graph transpose() {
        directed_graph gT {};
        int from {0};
        while (from < int(G.size())) {
            int to {0};
            while (to < int(G.at(from).size())) {
                if (!std::isnan(G.at(from).at(to)))
                    gT.add_edge(to, from, G.at(from).at(to));
                to++;
            }
            from++;
        }
        return gT;
    }

    directed_graph complement(double defaultValue=0) {
        directed_graph gC {};
        std::set<int> V {vertices()};
        int from {0};
        while (from < int(G.size())) {
            int to {0};
            while (to < int(G.at(from).size())) {
                if (std::isnan(G.at(from).at(to)) && V.count(from) && V.count(to))
                    gC.add_edge(from, to, defaultValue);
                to++;
            }
            from++;
        }
        return gC;
    }

    directed_graph subgraph(std::set<int> subgraphVertices) {
        directed_graph gS {};
        int from {0};
        while (from < int(G.size())) {
            int to {0};
            while (to < int(G.at(from).size())) {
                if (!std::isnan(G.at(from).at(to)) && subgraphVertices.count(from) && subgraphVertices.count(to)) {
                    gS.add_edge(from, to, G.at(from).at(to));
                }
                to++;
            }
            from++;
        }
        return gS;
    }

    bool is_reachable(const int from, const int to) {
        std::set<int> visited {from};
        std::list<int> todo {from};
        while (!todo.empty()) {
            int current {todo.front()};
            todo.pop_front();
            for (auto c : successors(current)) {
                if (c == to)
                    return true;
                else if (!visited.count(c)) {
                    visited.insert(c);
                    todo.push_back(c);
                }
            }
        }
        return false;
    }

    void print(std::string title="");
};


void directed_graph::print(std::string title) {
    std::set<int> setV {vertices()};
    std::set<std::pair<int,int>> setE {edges()};
    std::cout << "Graph " << title << ". It has " << setV.size() 
              << " vertices and "<< setE.size() << " edges" << std::endl;

    for (int v: setV) {
        std::cout << "Vertex [" ;
        std::cout << v ;
        std::cout << "]"<< std::endl;
     }

    for (auto e: setE) {
        assert(edge_exists(e.first, e.second));
        std::cout << "Edge [" << e.first << "] -> [" << e.second << "] weight [" << weight(e.first, e.second) << "]" << std::endl;
    }
}


#endif