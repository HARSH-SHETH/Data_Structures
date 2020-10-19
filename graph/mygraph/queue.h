#include <iostream>
#define MAXSIZE 100
using namespace std;

struct Q{
  int queue[MAXSIZE];
  int front;
  int rear;
  Q(): front{-1}, rear{-1} {}  
  void NQ(int vertex);
  int DQ();
};

void Q::NQ(int vertex){
  if(front == 0 && rear == MAXSIZE-1){
    cout << "overflow";
    exit(0);
  }
  if(front == rear+1){
    cout << "overflow";
    exit(0);
  }
  if(front == -1) {
    front++, rear++;
  }else if(rear == MAXSIZE-1){
    rear = 0;
  }else{
    rear++;
  }
  queue[rear] = vertex;
  return;
}

int Q::DQ(){
  if(front == -1) {
    return -1;
  }
  int item = queue[front];
  if(front == rear){
    front = rear = -1;
  }else if(front == MAXSIZE-1){
    front = 0;
  }else{
    front++;
  }
  return item;
}
