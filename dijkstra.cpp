#include "dijkstra.h"

Graph::Graph()
{
	prepareGraph();
}

DijkstraAlgorithm::DijkstraAlgorithm(Graph& graph)
{
    matrix = graph.getMatrix();
}

Element*  DijkstraAlgorithm::evaluate(int from, int destination)
{
    initializeSingleSource(from);

    std::map<int, Element*> Q;
    for (int i=0; i<MAX_SIZE;++i)
    {
       Q[i] = &dojscia[i];
    }

    auto min = [](auto lArg, auto rArg)-> bool
    {
       return lArg.second->sciezkaDojscia < rArg.second->sciezkaDojscia;
    };

    while (!Q.empty())
    {
       auto lowest = std::min_element( std::begin(Q), std::end(Q), min);
       std::cout<<"Lowest in the map is: " <<lowest->first << " " <<lowest->second->sciezkaDojscia << std::endl;
       for (int i = 0; i < MAX_SIZE; ++i)
       {
          if (matrix[lowest->first][i] != INF)
          {
            relax(lowest->first, i);
          }
       }
       Q.erase(lowest);
       }
     std::cout << "From the node: "<<from<<"to: "<< destination << " is : " << dojscia[destination].sciezkaDojscia << "\n";
}
void DijkstraAlgorithm::initializeSingleSource(int source)
{
   for (int i = 0;i < MAX_SIZE;++i)
   {
      dojscia[i].poprzednik = -1;
      dojscia[i].sciezkaDojscia = INF;
      dojscia[i].wierzcholek = i;
    }
    dojscia[source].poprzednik = -1;
    dojscia[source].sciezkaDojscia = 0;
}

void DijkstraAlgorithm::relax(int zrodlo, int destination)
{
   if( dojscia[destination].sciezkaDojscia > dojscia[zrodlo].sciezkaDojscia + matrix[zrodlo][destination])
   {
      dojscia[destination].sciezkaDojscia = dojscia[zrodlo].sciezkaDojscia + matrix[zrodlo][destination];
      dojscia[destination].poprzednik = destination;
   }
}


