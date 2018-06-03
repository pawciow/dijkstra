#include "prepareGraph.h"
#include "dijkstra.h"



int main()
{
    srand( time( NULL ) );
    Graph graf;
    DijkstraAlgorithm example(graf);
    example.evaluate(0,2);
    return 0;
}
