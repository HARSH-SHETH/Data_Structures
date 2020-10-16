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
  public: 
    Graph(): no_of_edges{0}, no_of_vertices{0}, directed{false},weighted{false}, edge_list{NULL} {}
    void init_graph(int,int, bool, bool); // initialize graph
    void insert_edge(int, int, int);
    void print_adjlist();
};
