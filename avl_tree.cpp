                 _       _         _          _       _     _   
 _   _ _ __   __| | __ _| |_ ___  | |__   ___(_) __ _| |__ | |_ 
| | | | '_ \ / _` |/ _` | __/ _ \ | '_ \ / _ \ |/ _` | '_ \| __|
| |_| | |_) | (_| | (_| | ||  __/ | | | |  __/ | (_| | | | | |_ 
 \__,_| .__/ \__,_|\__,_|\__\___| |_| |_|\___|_|\__, |_| |_|\__|
      |_|                                       |___/           
#include <iostream>
#define MAXSIZE 100
using namespace std;


struct node{
  int info;
  node *left; 
  node *right;
  int height;    // BALANCE FACTOR
};

class AVL_TREE{
  private: 
    node *root;
    int no_of_items;
    node *stack_tree[MAXSIZE];
    int top;
  public: 
    AVL_TREE(): root{NULL}, no_of_items{0}, top{-1} {}
    int get_no_of_items() { return no_of_items; }
    void insert_tree(node*);
    void balance_tree(node*);
    int get_bf(node* ptr) { return get_height(ptr->left) - get_height(ptr->right); }
    int get_height(node* ptr) { return (ptr == NULL) ? 0 : ptr->height;}
    void right_rotation(node*, node*);
    void left_rotation(node*, node*);
    node* find_node(int);
    node* find_parent(int);
    void print_array(int*, int, string);
    int* preorder(void);
    int* inorder(void);
    int* postorder(void);

    node* get_node(int info){
      node *item = new node;
      item->left = item->right = NULL;
      item->info = info;
      item->height = 1; // INITIALLY ALL NODES ARE LEAF
      return item;
    }
};

//INSERT ITEMS INTO THE BINARY TREE
void AVL_TREE::insert_tree(node *item){
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
    else if(item->info > save->info)
      save->right = item;
    else 
      return;
  }
  no_of_items++;
  balance_tree(item);
  return;
}

// BALANCE TREE USING LEFT AND RIGHT ROTATIONS 
void AVL_TREE::balance_tree(node *item){
  int bf = 0;
  node *ptr = new node;
  ptr = root;
  bool node_unbalanced = false;
  while(ptr != NULL){
    bf = get_bf(ptr);
    if(bf == 2 || bf == -2){
      stack_tree[++top] = ptr;
      node_unbalanced = true;
    }
    if(item->info < ptr->info)
      ptr = ptr->left;
    else 
      ptr = ptr->right;
  }
  if(node_unbalanced){
    ptr = stack_tree[top];
    node *parent_node = find_parent(ptr->info);
    if(get_bf(ptr) == 2){
      ptr = stack_tree[top];
      if(item->info < ptr->left->info)
        // LEFT LEFT CASE
        right_rotation(ptr, parent_node);  
      else{   
        // LEFT RIGHT CASE
        left_rotation(ptr->left, ptr); 
        right_rotation(ptr, parent_node);
      }
    }else{
      if(item->info > ptr->right->info){
        // RIGHT RIGHT CASE
        left_rotation(ptr, parent_node);
      }
      else{
        // RIGHT LEFT CASE
        right_rotation(ptr->right, ptr);
        left_rotation(ptr, parent_node);
      }
    }
  }else{ cout << "Balance Not Affected"; }
  top = -1;
  return;
}

// ROTATE THE SUB-TREE ANTI-CLOCKWISE AROUND PIVOT NODE
void AVL_TREE::left_rotation(node *pivot_node, node *parent_node){
  if(parent_node != NULL){
    if(parent_node->left == pivot_node){
      parent_node->left = pivot_node->right;
    }else{
      parent_node->right = pivot_node->right;
    }
  }
  node *save = pivot_node->right;
  pivot_node->right = save->left;
  save->left = pivot_node;
  if(parent_node == NULL) { root = save; }
  return;
}

// FIND A NODE AN RETURN ITS ADDRESS
node* AVL_TREE::find_node(int item){
  if(root == NULL){
    cout << "Go Make A Tree First";
    return NULL;
  }
  node *ptr = new node;
  ptr = root;
  while(ptr != NULL){
    if(item == ptr->info) return ptr;
    if(item < ptr->info){
      ptr = ptr->left;
    }else{
      ptr = ptr->right;
    }
  }
  return NULL;
}

// FIND A NODE AN RETURN ITS PARENT'S ADDRESS
node* AVL_TREE::find_parent(int item){
  node *ptr = new node;
  node *parent = new node;
  ptr = root;
  parent = NULL;
  while(ptr != NULL){
    if(item == ptr->info) return parent;
    parent = ptr;
    if(item < ptr->info){
      ptr = ptr->left;
    }else{
      ptr = ptr->right;
    }
  }
  return NULL;
}

// ROTATE THE SUB-TREE CLOCKWISE AROUND PIVOT NODE
void AVL_TREE::right_rotation(node *pivot_node, node *parent_node){
  if(parent_node != NULL){
    if(parent_node->left == pivot_node){
      parent_node->left = pivot_node->left;
    }else{
      parent_node->right = pivot_node->left;
    }
  }
  node *save = pivot_node->left;
  pivot_node->left = save->right;
  save->right = pivot_node;
  if(parent_node == NULL) { root = save; }
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

int main(){
  int info;
  AVL_TREE T;
  while(cin >> info && info != -1){
    T.insert_tree(T.get_node(info));
  }
  T.print_array(T.inorder(), T.get_no_of_items(), "INORDER IS: ");
  return 0;
}
