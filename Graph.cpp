#include "Graph.hpp"
#include <fstream>
#include <sstream>

namespace VertexCover{
    Graph readFromFile(const std::string& filename) {
        Graph graph;  
        std::ifstream file(filename);  
    
        if (!file.is_open()) {  
            throw std::runtime_error("Could not open file");
        }
    
        std::string line;
        while (std::getline(file, line)) {  
            if (line.empty()) continue;
    
            size_t dep_start = line.find("- ") + 2;  
            size_t dep_end = line.find(' ', dep_start);  
            size_t dest_start = line.find("- ", dep_end) + 2;  
            size_t dest_end = line.find(' ', dest_start);  
    
            std::string source = line.substr(dep_start, dep_end - dep_start);
            std::string destination = line.substr(dest_start, dest_end - dest_start);
    
            source.erase(std::remove(source.begin(), source.end(), '|'), source.end());
            destination.erase(std::remove(destination.begin(), destination.end(), '|'), destination.end());
    
            graph[source].insert(destination);
            graph[destination].insert(source);
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
