#include "graph2.cpp"
#include "input.h"
using namespace std;

int main(){
  Graph G;
  int vertex;
  char ch;
  graph_input(G);
  G.bfs_graph(bfs_input(G));
  cout << "\n Enter endpoint";
  cin >> ch;
  G.find_path(ctoi(ch));
  return 0;
}
