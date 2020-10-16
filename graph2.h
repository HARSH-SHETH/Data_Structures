#include <iostream>
using namespace std;
struct edgenode{
  int adj;
  int weight;
  edgenode *next_edge;
};
class Graph{
  private: 
    int no_of_vertices;
    int no_of_edges;
    bool directed;
    edgenode *edge_list;
  public: 
    Graph(): no_of_edges{0}, no_of_vertices{0}, directed{false}, edge_list{NULL} {}
    void init_graph(int, bool); // initialize graph
};

void Graph::init_graph(int vertices, bool directed){
  edge_list = new edgenode[vertices];
  this->no_of_vertices = vertices;
  this->directed = directed;
}
