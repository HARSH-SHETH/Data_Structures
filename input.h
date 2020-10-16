#include <iostream>
using namespace std;

void graph_input(Graph &G){
  int no_of_vertices; 
  char ch; 
  bool directed;
  cout << "Enter the no of vertices: ";
  cin >> no_of_vertices;
  cout << "\n Is graph directed(y or n): ";
  cin >> ch;
  directed = (ch == 'n') ? false : true; 
  G.init_graph(no_of_vertices, directed);
  return;
}
