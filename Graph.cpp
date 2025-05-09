#include "Graph.hpp"
#include <fstream>
#include <sstream>

namespace VertexCover{

    Graph readFromFile(const std::string& filename){
        Graph graph;
        std::ifstream file(filename);

        if(file.fail()){
            throw std::runtime_error("Could not open file");
        }

        std::string line;
        while(std::getline(file,line)){
            std::istringstream iss(line);
            std::string source, destination;
            
            if(iss >> source >> destination){
                graph[source].insert(destination);
                graph[destination].insert(source);
            }
        }
        return graph;
    }

    std::unordered_set<Vertex> cover_graph(Graph g) {
        std::unordered_set<Vertex> cover;
        
        while (true) {
            Vertex max_vertex;
            size_t max_degree = 0;
            bool edges_remain = false;
            
            for (const auto& [vertex, neighbors] : g) {
                if (!neighbors.empty()) {
                    edges_remain = true;
                    if (neighbors.size() > max_degree) {
                        max_degree = neighbors.size();
                        max_vertex = vertex;
                    }
                }
            }
            if (!edges_remain) break;
            
            cover.insert(max_vertex);
            
            for (const auto& neighbor : g[max_vertex]) {
                g[neighbor].erase(max_vertex);
            }
            
            g.erase(max_vertex);
        }
        return cover;
    }

}