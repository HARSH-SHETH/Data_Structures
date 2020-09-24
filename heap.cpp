#include <iostream>
#include <ctype.h>
#include <string.h>
#define MAXSIZE 1000
using namespace std;

class HEAP{
  private: 
    int heap[MAXSIZE];
    int current_node;
  public: 
    HEAP(): current_node{-1} {}
    void insert_heap(int key);
    int get_parent(int i) { return (i%2 == 0) ? i/2-1 : i/2; }
    void swap(int i, int j){
      int temp;
      temp = heap[i], heap[i]  = heap[j], heap[j]  = temp;
      return;
    }
    void print_heap(int arr[], int, string);
};

// PRINT ARRAY WITH MSG
void HEAP::print_heap(int arr[], int size, string msg){
  cout << msg;
  for(int i = 0; i < size; i++){
    cout << arr[i];
    if(i != size-1) cout << ", ";
  }
  cout << "\n";
}

// INSERT ELEMENTS AT APPROPRIATE POSITION IN HEAP
void HEAP::insert_heap(int key){
  if(++current_node >= MAXSIZE) {
    cout << "Segmentation Fault";
    return;
  }
  int ptr = current_node;

  heap[ptr] = key;
  int parent;
  if((parent = get_parent(ptr)) == -1) { return; }
  while(heap[ptr] > heap[parent]){
    swap(ptr, parent);
    parent = get_parent(ptr = parent);
  }
  print_heap(heap, current_node+1, "current heap is: ");
  return;
}

int main(){
  HEAP H;
  int num;
  while(cin >> num && num != -1){
    H.insert_heap(num);
  }
  return 0;
}
