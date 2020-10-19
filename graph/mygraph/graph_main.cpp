#include "graph2.cpp"
#include "input.h"
using namespace std;

int main(){
  Graph G;
  int vertex;
  graph_input(G);
  G.bfs_graph(bfs_input(G));
  return 0;
}
