#ifndef _GRAPH
#define _GRAPH

#include "const.h"

class prepareGraph
{
 public:
  prepareGraph();
  virtual int **getMatrix();
 protected:
  int** matrix = new int* [MAX_SIZE];
  void initailizeMatrix() const;
  virtual void randomizeGraph();
  virtual void readData();
};
#endif
