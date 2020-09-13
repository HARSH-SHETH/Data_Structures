#include <iostream>
using namespace std;

struct node{
  node *left; 
  node *right;
  int info;
};

class TREE{
  private: 
    node *root;
    int no_of_items;
  public: 
    TREE(): root{NULL}, no_of_items{0} {}
    void insert_tree(node*);
};

void TREE::insert_tree(node *item){
  if (root == NULL){
    root = item;
  }else{
    node *temp = new node;
    temp = root;
  }
}
int main(){
  return 0;
}
