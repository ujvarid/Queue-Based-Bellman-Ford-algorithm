#ifndef __QBF__
#define __QBF__

#include <list>
#include <string>
#include <map>
#include <queue>
#include <iostream>
#include <utility> 
#include <algorithm>
#include <fstream>
#include <sstream>
#include <set>

#define INFINITY 99999
#define NO_PARENT "no_parent"

class QBF 
{
private:
    // has there been a shortest path computed
    bool _computed;

    // the nodes of the graph are in the map, as a name and adjacency list representation, within that: name, cost
    std::map<std::string, std::list<std::pair<std::string, int>> > _graph;
    // the names of the nodes
    std::set<std::string> _node_names;
    // distances from the start node
    std::map<std::string, int> _distances;
    // the first parameter's parent is the second parameter in the shortest path from the source node to the destination
    std::map<std::string, std::string> _parents;
    // number of edges that it takes to get to the given node
    std::map<std::string, unsigned int> _edges;
    std::list<std::string> _shortest_path;

public:

    // input a graph, scheme: name: node_name, cost; node_name1, cost1;
    QBF(const std::string&);
    void print_graph() const;
    
    // compute the shortest path starting from the first parameter, to the second
    void compute_shortest_paths(const std::string&);

    // get shortest path from the computed source node
    void get_shortest_path(const std::string&);

    // print the shortest path calculated
    void print_shortest_path();    
};

#endif