#include <iostream>
#include "queue.h"
#define MAXNODE 100
#define UNDISCOVERED -1
#define DISCOVERED    0 
#define PROCESSED     1 
#define NOPARENT     -1 
using namespace std;

struct edgenode{
  int adj;
  int weight;
  edgenode *next;
};

struct graph{
  edgenode *edges[MAXNODE+1]; // Adjacency List(Array of linked lists)
  int outdegree[MAXNODE+1];  // OUTDEGREE OF EACH NODE
  int nvertices;
  int nedges;
  bool directed;
};

void initialize_graph(graph *g, bool directed){
  g->nvertices = 0; // INITIALLY THERE ARE NO VERTICES
  g->nedges = 0;  // THEREFORE NO EDGES ALSO
  g->directed = directed;
  for(int i = 0; i < MAXNODE+1; i++){
    g->edges[i] = NULL; // ADJACENCY LIST WILL BE NULL INITIALLY
    g->outdegree[i] = 0; // OUTDEGREE WILL BE ZERO AS NO NODES ARE PRESENT
  }
  return;
}

void insert_edge(graph *g, int x, int y, bool directed, int weight=0){
  edgenode *e = new edgenode; // TEMPERORY EDGENODE
  e->weight = weight;
  e->adj = y;
  // INSERT IN THE FRONT OF THE EDGE LIST
  e->next = g->edges[x];  
  g->edges[x] = e;

  if(!directed)
    insert_edge(g, y, x, true, weight);
  else
    g->nedges++;
  return;
}

void build_graph(graph *g, bool directed){
  int n, m;
  char x, y;
  initialize_graph(g, directed);
  cout << "Enter no. of vertices and edges: ";
  cin >> n >> m;
  if(n == 0) { exit(0); }
  g->nvertices = n; // TOTAL NO OF NODES IN GRAPH
  for(int i = 0; i < m; i++){
    cout << "\nEnter edge to be inserted: \n source vertex: ";
    cin >> x;
    cout << "Destination vertex: ";
    cin >> y;
    insert_edge(g, ctoi(x) , ctoi(y), directed);
  }
  return;
}

void print_graph(graph *g){
  prettify();
  edgenode *ptr = new edgenode;
  for(int i = 0; i < g->nvertices; i++){
    cout << "\nEdgelist of node "; putchar(i + 'A'); cout << ": ";
    ptr = g->edges[i];
    while(ptr != NULL){
      cout << "{"; putchar(ptr->adj + 'A'); cout << "}, ";
      ptr = ptr->next;
    }
  }
  prettify();
  return;
}

// BFS of graph
void bfs(graph *g, int source){
  if(source < 0 || source > g->nvertices) {
    cout << "wrong input";
    exit(-1);
  }
  int *state = new int[g->nvertices];
  int *parent = new int[g->nvertices];
  for(int i = 0; i < g->nvertices; i++) {
    state[i] = UNDISCOVERED;  // initially every node is undiscovered
    parent[i] = NOPARENT;
  }
  state[source] = 0;  // DISCOVERED
  Enqueue(source);
  int vertex;
  while((vertex = Dequeue()) != -1){
    cout << "\nCurrent Vertex is: " << itoc(vertex);
    edgenode *ptr = g->edges[vertex];
    while(ptr != NULL){
      if(state[ptr->adj] == UNDISCOVERED){
        cout << "\n-> \tcurrent edges is: {" << itoc(vertex) << ", " << itoc(ptr->adj) << "}";
        state[ptr->adj] = DISCOVERED;
        parent[ptr->adj] = vertex;
        Enqueue(ptr->adj);
      }
      ptr = ptr->next;
    }
    state[vertex] = PROCESSED;
  }
  prettify();
  for(int i = 0; i < g->nvertices; i++){
    cout << "\nParent of vertex: " << itoc(i) << "is: " << itoc(parent[i]);
  }
  return;
}

int main(){
  graph *new_graph = new graph;
  char ch;
  int source;
  cout << "Press 'y' or 'n'\n";
  cout << "Is graph directed: ";
  cin >> ch;
  build_graph(new_graph, (ch == 'y') ? true : false);
  print_graph(new_graph);
  cout << "\n Enter the source node: ";
  cin >> ch;
  source = ctoi(ch);
  if(source >= new_graph->nvertices || source < 0){
    cout << "No such node found";
    return -1;
  }
  bfs(new_graph, source);
  return 0;
}
