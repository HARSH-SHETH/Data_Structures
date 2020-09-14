#include <iostream>
using namespace std;
#define MAXSIZE 100

struct node{
  node *left; 
  node *right;
  int info;
};

void print_array(int *arr, int size, string msg){
  cout << "\n" << msg;
  for(int i = 0; i < size; i++){
    cout << arr[i];
    if (i != size-1)  cout << ", ";
  }
}

class TREE{
  private: 
    node *root;
    int no_of_items;
    node *stack_tree[MAXSIZE];
    int top;
  public: 
    TREE(): root{NULL}, no_of_items{0}, top{-1} {}
    int get_no_of_items(void){ return no_of_items; }
    void insert_tree(node*);
    int* preorder(void);
    int* inorder(void);
};

void TREE::insert_tree(node *item){
  if (root == NULL){
    root = item;
  }else{
    node *temp = new node;
    node *save = new node;
    temp = root;
    while(temp != NULL){
      save = temp;
      if (item->info < temp->info)
        temp = temp->left;
      else
        temp = temp->right;
    }
    if (item->info < save->info)
      save->left = item;
    else
      save->right = item;
  }
  no_of_items++;
}

int* TREE::preorder(void){
  int *preorder_tree = new int[no_of_items-1];
  int index = -1;
  stack_tree[++top] = NULL;
  node *ptr = new node;
  ptr = root;
  while(ptr != NULL){
    preorder_tree[++index] = ptr->info;
    if(ptr->right != NULL){
      stack_tree[++top] = ptr->right;
    }
    if(ptr->left != NULL){
      ptr = ptr->left;
    }else{
      ptr = stack_tree[top--];
    }
  }
  return preorder_tree;
}
int main(){
  int info;
  TREE T;
  while(cin >> info){
    node *item = new node;
    item->info = info;
    item->left = NULL;
    item->right = NULL;
    T.insert_tree(item);
  }
  int *preorder = T.preorder();
  print_array(preorder, T.get_no_of_items(), "Preorder is: ");
  return 0;
}
