#ifndef _DIJKSTRA
#define _DIJKSTRA

#include "prepareGraph.h"

struct Element
{
	 int poprzednik = -1;
	 int sciezkaDojscia = INF;
	 int wierzcholek;
};
class Graph : public prepareGraph
{
public:
    Graph();
};


class DijkstraAlgorithm
{
public:
 DijkstraAlgorithm(Graph& graph);
 Element*  evaluate(int from, int destination);

private:
 void initializeSingleSource(int source);
 void relax(int zrodlo, int destination);
 Element dojscia[MAX_SIZE];
 int** matrix;
};

#endif
