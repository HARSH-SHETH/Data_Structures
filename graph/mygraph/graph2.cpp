#include "graph2.h"
#include "queue.h"
#define UNDISCOVERED -1
#define DISCOVERED    0
#define PROCESSED     1
#define NOPARENT     -1
using namespace std;

void Graph::init_graph(int nvertices,int nedges,  bool directed, bool weighted){
  edge_list = new edgenode*[nvertices];
  parent = new int[nvertices];
  state = new int[nvertices];
  for(int i = 0; i < nvertices; i++){
    edge_list[i] = NULL;
    parent[i] = NOPARENT;
    state[i]  = UNDISCOVERED;
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

void Graph::bfs_graph(int source){
  int current_vertex;
  for(int i = 0; i < no_of_vertices; i++){
    parent[i] = NOPARENT;
    state[i] = UNDISCOVERED;
  }
  Q q;
  q.NQ(source);
  state[source] = DISCOVERED;
  edgenode *e;
  while((current_vertex = q.DQ()) != -1){
    process_vertex_early(current_vertex);
    state[current_vertex] = PROCESSED;
    e = edge_list[current_vertex];
    while(e != NULL){
      if(state[e->adj] == UNDISCOVERED){
        state[e->adj] = DISCOVERED;
        parent[e->adj] = current_vertex;
        q.NQ(e->adj);
/*        process_edge(current_vertex, e->adj);*/
      }
      if(state[e->adj] == DISCOVERED || directed){
        state[e->adj] = PROCESSED;
        process_edge(current_vertex, e->adj);
      }
      e = e->next_edge;
    }
    process_vertex_late(current_vertex);
  }
  return;
}

void Graph::find_path(int endpoint){
  if(parent[endpoint] == -1){
    printf("%c", itoc(endpoint));
  }else{
    find_path(parent[endpoint]);
    printf("->%c", itoc(endpoint));
  }
}
