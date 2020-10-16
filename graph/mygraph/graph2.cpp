#include "graph2.h"
using namespace std;

void Graph::init_graph(int nvertices,int nedges,  bool directed, bool weighted){
  edge_list = new edgenode*[nvertices];
  for(int i = 0; i < nvertices; i++){
    edge_list[i] = NULL;
  }
  this->no_of_vertices = nvertices;
  this->no_of_edges = nedges;
  this->directed = directed;
  this->weighted = weighted;
}

void Graph::insert_edge(int u, int v, int weight = 0){
  edgenode *p = new edgenode;
  p->adj = v;
  p->weight = weight;
  p->next_edge = NULL;
  edgenode *tmp = new edgenode;
  edgenode *save = new edgenode;
  tmp = edge_list[u];
  save = NULL;
  if(tmp == NULL){
    edge_list[u] = p;
  }else{
    while((tmp != NULL) && (p->adj > tmp->adj)){
      save = tmp;
      tmp = tmp->next_edge;
    }
    if(save == NULL){
      p->next_edge = edge_list[u];
      edge_list[u] = p;
    }else{
      p->next_edge = save->next_edge;
      save->next_edge = p;
    }
  }
  cout << "edge inserted";
  return;
}

void Graph::print_adjlist(){
  for(int i = 0; i < no_of_vertices; i++){
    edgenode *ptr = new edgenode;
    ptr = edge_list[i];
    printf("\nAdjacency list of %c: ", itoc(i));
    while(ptr != NULL){
      cout << itoc(ptr->adj) << " :) ";
      ptr = ptr->next_edge;
    }
  }
}
