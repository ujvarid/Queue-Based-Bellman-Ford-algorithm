#include "qbf.h"

QBF :: QBF(const std::string& file_name_) : _computed(false)
{
    std::ifstream file(file_name_);
    if (!file.is_open())
    {
        std::cerr << "Error opening the file\n";
        return;
    }

    std::string tmp_line;

    while (std::getline(file, tmp_line))
    {
        std::istringstream line_stream(tmp_line);

        std::string name_part, node_name;
        if (!std::getline(line_stream, name_part, ':')) 
        {
            continue;
        }
        node_name = name_part;
        _node_names.insert(node_name);
        
        std::string adj_part;
        while (std::getline(line_stream, adj_part, ';'))
        {
            std::istringstream adj_stream(adj_part);
            std::string neighbor_name;
            int cost;

            if (std::getline(adj_stream, neighbor_name, ',') && (adj_stream >> cost))
            {
                _graph[node_name].emplace_back(neighbor_name, cost);
                _node_names.insert(neighbor_name);
            }
        }
    }

    for (const auto& [node, adjacency_list] : _graph) // AHONNAN NEM MEGY EL AZ NINCS BENNE!!
    {
        _node_names.insert(node);
    }
}

void QBF :: print_graph() const 
{
    std::cout<<"The given graph:\n\n"; 

    for (const auto& [node, adjacency_list] : _graph)
    {
        std::cout << node << " -> ";
        for (const auto& [neighbor, cost] : adjacency_list)
        {
            std::cout << "(" << neighbor << ", " << cost << ") ";
        }
        std::cout << '\n';
    }
}

void QBF :: compute_shortest_paths(const std::string& source_)
{
    if(_node_names.find(source_) == _node_names.end()) 
    { 
        std::cerr<< "\n>>Invalid source node<<\n"; 
        return;
    }

    // to check whether a node is in the queue
    std :: map<std::string, bool> in_queue;
    for(auto it = _node_names.begin(); it != _node_names.end(); ++it)
    {
        _distances[*it] = INFINITY ;
        _parents[*it] = NO_PARENT;
        in_queue[*it] = false;
    }

    _distances[source_] = 0; 
    _edges[source_] = 0;

    std::queue<std::string> queue;

    queue.push(source_);
    in_queue[source_] = true;

    while (!queue.empty())
    {
        std::string current_node = queue.front(); 
        queue.pop();

        in_queue[current_node] = false;

        auto& adj_list = _graph[current_node];

        // nodes that can be reached from current_node        
        for(auto v = adj_list.begin(); v != adj_list.end(); ++v)
        {
            if(_distances[v->first] > _distances[current_node] + v->second)
            {
                _distances[v->first] = _distances[current_node] + v->second;
                _parents[v->first] = current_node;
                _edges[v->first] = _edges[current_node] + 1;
                if(_edges[v->first] >= _graph.size()) 
                { 
                    std::cerr << "\n>>Negative cycle<<\n"; return;
                }
                if(!in_queue[v->first])
                {
                    queue.push(v->first);
                    in_queue[v->first] = true;
                }
            }   
        }
    }

    _computed = true;
}

void QBF :: get_shortest_path(const std::string& dest_)
{
    if(_node_names.find(dest_) == _node_names.end()) 
    { 
        std::cerr<< "\n>>Invalid destination node<<\n"; 
        return;
    }

    if(!_computed) { std::cerr << "\n>>A source node was not yet given<<\n"; return;  }

    if(_distances[dest_] == INFINITY) 
    { 
        std::cerr << "\n>>The given node is unreachable from the source node<<\n"; return; 
    }

    std::string tmp_node = dest_;

    while (_parents[tmp_node] != NO_PARENT)
    {
        _shortest_path.push_front(tmp_node);
        tmp_node = _parents[tmp_node];
    }

    _shortest_path.push_front(tmp_node);
}

void QBF :: print_shortest_path()
{
    if(!_computed || _shortest_path.size() == 0) { return;  }

    std::cout << "\nThe shortest path from " << *_shortest_path.begin() << " to " << _shortest_path.back() << ":\n\n";

    for (auto it = _shortest_path.begin(); it != _shortest_path.end(); ++it)
    {
        std::cout << *it;
        if (std::next(it) != _shortest_path.end()) // Ellenőrizd, hogy van-e következő elem
        {
            std::cout << " -> ";
        }
        else
        {
            std::cout << "\tcost: " << _distances[*it];
        }
    }

    std::cout << std::endl;
}