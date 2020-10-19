#include <iostream>
#ifndef HELPER_H
#define HELPER_H
#include "helper.h"
#endif
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
    bool weighted;
    edgenode **edge_list;
    int *parent, *state;
  public: 
    Graph(): no_of_edges{0}, no_of_vertices{0}, directed{false},weighted{false}, edge_list{NULL}, parent{NULL}, state{NULL} {}
    void init_graph(int,int, bool, bool); // initialize graph
    void insert_edge(int, int, int);
    void print_adjlist();
    void bfs_graph(int);
    int get_no_of_vertices(){ return no_of_vertices; }
    void process_vertex_early(int);
    void process_edge(int, int);
    void process_vertex_late(int);
};

void Graph::process_vertex_early(int vertex){
  printf("\n****************\nprocessed early: %c", itoc(vertex));
}
void Graph::process_edge(int u, int v){
  printf("\n\t current edge: %c->%c", itoc(u), itoc(v));
}
void Graph::process_vertex_late(int vertex){ 
  printf("\n processed late: %c\n*************\n", itoc(vertex));
}
