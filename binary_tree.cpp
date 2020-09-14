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
    int* postorder(void);
};

//INSERT ITEMS INTO THE BINARY TREE
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

// RETURN AN ARRAY CONTAINING PREORDER
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

// RETURN AN ARRAY CONTAINING INORDER
int* TREE::inorder(void){
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
int* TREE::postorder(void){
}

// MAIN
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
  print_array(T.preorder(), T.get_no_of_items(), "Preorder is: ");
  print_array(T.inorder(), T.get_no_of_items(), "Inorder is: ");
  print_array(T.postorder(), T.get_no_of_items(), "Postorder is: ");
  return 0;
}
