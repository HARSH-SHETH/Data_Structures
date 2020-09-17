#include <iostream>
using namespace std;

struct node{
  int info;
  node *left; 
  node *right;
  int count;
  int BF;    // BALANCE FACTOR
};

class AVL_TREE{
  private: 
    node *root;
    int no_of_nodes;
    node *stack_tree[MAXSIZE];
    int top;
  public: 
    AVL_TREE(): root{NULL}, no_of_nodes{0}, top{-1} {}
    node* insert_node(int key);
    void right_rotation(node*);
    void left_rotation(node*);
    node* find_node(int);
    node* find_parent(int);
    void print_array(int*, int, string);
    int* preorder(void);
    int* inorder(void);
    int* postorder(void);

};

// ROTATE THE SUB-TREE ANTI-CLOCKWISE AROUND PIVOT NODE
void AVL_TREE::left_rotation(node *pivot_node, node *parent_node){
  if(parent_node->left == pivot_node){
    parent_node->left = pivot_node->right;
  }else{
    parent_node->right = pivot_node->right;
  }
    node *save = pivot_node->right;
    pivot_node->right = save->left;
    save->left = pivot_node;
  return;
}

// ROTATE THE SUB-TREE CLOCKWISE AROUND PIVOT NODE
void AVL_TREE::right_rotation(node *pivot_node, node *parent_node){
  if(parent_node->left == pivot_node){
    parent_node->left = pivot_node->left;
  }else{
    parent_node->right = pivot_node->left;
  }
  node *save = pivot_node->left;
  pivot_node->left = save->right;
  save->right = pivot_node;
  return;
}

// PRINT ARRAY 
void AVL_TREE::print_array(int *arr, int size, string msg){
  if(size <= 0 || arr == NULL){ 
    cout << "\nEmpty Tree: ";
    return;
  }
  cout << "\n" << msg;
  for(int i = 0; i < size; i++){
    cout << arr[i];
    if (i != size-1)  cout << ", ";
  }
}

// RETURN AN ARRAY CONTAINING PREORDER
int* AVL_TREE::preorder(void){
  if(get_no_of_items() == 0){
    return NULL;
  }
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

// RETURN AN ARRAY CONTAINING INORDER
int* AVL_TREE::inorder(void){
  if(get_no_of_items() == 0){
    return NULL;
  }
  int *inorder_tree = new int[get_no_of_items()-1];
  int index = -1;
  stack_tree[++top] = NULL;
  node *ptr = new node;
  ptr = root;
  while(ptr != NULL){
    while(ptr != NULL){
      stack_tree[++top] = ptr;
      ptr = ptr->left;
    }
    do{
      ptr = stack_tree[top--];
      if(ptr != NULL){
        inorder_tree[++index] = ptr->info;
      }else{
        break;
      }
    }while(ptr->right == NULL && ptr != NULL);
    if(ptr != NULL){
      if(ptr->right != NULL){ 
        ptr = ptr->right;
      }
    }
  }
  return inorder_tree;
}

// RETURN AN ARRAY CONTAINING POSTORDER
int* AVL_TREE::postorder(void){
  if(get_no_of_items() == 0){
    return NULL;
  }
  int *postorder_tree = new int[get_no_of_items()-1];
  int index = -1;
  int sign[get_no_of_items()-1];
  sign[0] = 0;
  stack_tree[++top] = NULL;
  node *ptr = new node;
  ptr = root;
  while(ptr != NULL){
    while(ptr != NULL){
      stack_tree[++top] = ptr;
      sign[top] = 1;
      if(ptr->right != NULL){
        stack_tree[++top] = ptr->right;
        sign[top] = -1;
      }
      ptr = ptr->left;
    }
    while(sign[top] > 0){
      postorder_tree[++index] = stack_tree[top--]->info;
    }
    if(sign[top] < 0) ptr = stack_tree[top--];
  }
  return postorder_tree;
}
