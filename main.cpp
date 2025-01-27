#include "qbf.h"

int main() 
{
    QBF qbf("graph.txt");
    qbf.print_graph();
    qbf.compute_shortest_paths("a");
    qbf.get_shortest_path("b");
    qbf.print_shortest_path();
    return 0;
}