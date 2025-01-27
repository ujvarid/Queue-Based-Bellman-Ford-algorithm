#include "qbf.h"

int main(int argv, char * argc[]) 
{
    if(argv != 3) { std::cerr << "Incorrect parameters\n" ; return 1;}
    QBF qbf("12th_district_streets.txt");
    // qbf.print_graph();
    qbf.compute_shortest_paths(argc[1]);
    qbf.get_shortest_path(argc[2]);
    qbf.print_shortest_path();
    return 0;
}
