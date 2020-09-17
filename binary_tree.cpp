#include <iostream>
using namespace std;
#define MAXSIZE 100

struct node{
  node *left; 
  node *right;
  int info;
};

void print_array(int *arr, int size, string msg){
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

class TREE{
  private: 
    node *root;
    int no_of_items;
    node *stack_tree[MAXSIZE];
    int top;
  public: 
    TREE(): root{NULL}, no_of_items{0}, top{-1} {}
    bool is_tree_empty() { return (root == NULL) ? true : false;}
    int get_no_of_items(void){ return no_of_items; }
    void insert_tree(node*);
    int* preorder(void);
    int* inorder(void);
    int* postorder(void);
    node* find_node(int);
    node* find_parent(int);
    node* find_inorder_suc(node*);
    void delete_node(node*);
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
int* TREE::inorder(void){
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
int* TREE::postorder(void){
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

// FIND A NODE AN RETURN ITS ADDRESS
node* TREE::find_node(int item){
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
node* TREE::find_parent(int item){
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

// DELETE THE SPECIFIED NODE
void TREE::delete_node(node *ptr){
  node *parent = find_parent(ptr->info);
  if(ptr->left != NULL && ptr->right != NULL){
    node *SUC = new node;
    SUC = find_inorder_suc(ptr);
    int save = SUC->info;
    delete_node(SUC);
    ptr->info = save;
  }else{
    if(parent == NULL){
      if(ptr->left != NULL){
        root = ptr->left;
      }else{
        root = ptr->right;
      }
      no_of_items--;  // DECREMENT ONLY WHEN NODE HAS ONE OR ZERO CHILD;
      return;
    }
    node *child = new node;
    if(ptr->left != NULL){
      child = ptr->left;
    }else{
      child = ptr->right;
    }
    if(parent->left == ptr){
      parent->left = child;
    }else{
      parent->right = child;
    }
    no_of_items--;  // DECREMENT ONLY WHEN NODE HAS ONE OR ZERO CHILD;
  }
  return;
}

// FIND THE INORDER SUCCESSOR OF THE CURRENT NODE
node* TREE::find_inorder_suc(node* ptr){
  node *SUC = new node;
  SUC = ptr->right;
  while(SUC->left != NULL){
    SUC = SUC->left;
  }
  cout << "inorder succesor is: " << SUC->info;
  return SUC;
}

// MAIN
int main(){
  int info;
  TREE T;
  while(cin >> info && info != -1){
    node *item = new node;
    item->info = info;
    item->left = NULL;
    item->right = NULL;
    T.insert_tree(item);
  }
  print_array(T.preorder(), T.get_no_of_items(), "Preorder is: ");
  print_array(T.inorder(), T.get_no_of_items(), "Inorder is: ");
  print_array(T.postorder(), T.get_no_of_items(), "Postorder is: ");
  while(true){
    if(T.is_tree_empty()) {
      cout << "\nTree has been cut, plant a new one";
      return -1;
    }
    cout << "\nEnter any item to be searched";
    cin >> info;
    node* item = T.find_node(info);
    if(item != NULL) {
      cout << "\nItem Found";
      if(T.find_parent(info) != NULL){
        cout << "\t Parent Node: " << T.find_parent(info)->info;
      }else{
        cout << "\tRoot of the Tree";
      }
    }else cout << "\nItem Not Found";
    T.delete_node(item);
    print_array(T.inorder(), T.get_no_of_items(), "Inorder is: ");
  }
  return 0;
}
