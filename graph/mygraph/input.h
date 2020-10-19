#include <iostream>
#include <ctype.h>
#ifndef HELPER_H
#define HELPER_H
#include "helper.h"
#endif
#ifndef REP
#define REP(i,a,n) for(int i = a; i <= n; i++)
#endif

using namespace std;

void graph_input(Graph &G){
  int no_of_vertices, no_of_edges; 
  char ch; 
  bool directed, weighted;
  cout << "Enter the no of vertices and edges: ";
  cin >> no_of_vertices >> no_of_edges;
  directed = isSomething("directed");
  weighted = isSomething("weighted");
  G.init_graph(no_of_vertices, no_of_edges, directed, weighted);
  REP(i,1,no_of_edges){
    char chu, chv;  // u,v pairs
    int weight = 0;
    cout << "\n Enter Edge Pairs(eg: A B)";
    cin >> chu >> chv;
    check_bound(ctoi(chu), ctoi(chv), no_of_vertices);
    if(weighted){
      cout << "Enter weight of the edge: ";
      cin >> weight;
      G.insert_edge(ctoi(chu), ctoi(chv), weight);
    }else{
      G.insert_edge(ctoi(chu), ctoi(chv));
    }
    if(!directed) G.insert_edge(ctoi(chv), ctoi(chu), weight);
  }
  G.print_adjlist();
}

int bfs_input(Graph &G){
  int source;
  char ch;
  cout << "\n Enter Source Vertex: ";
  cin >> ch;
  source = ctoi(ch);
  if(source > G.get_no_of_vertices() || source < 0){
    cout << "node does not exist";
    exit(0);
  }
  return source;
}
