#include <iostream>
using namespace std;

char itoc(int num){
  return num+'A';
}

int ctoi(char ch){
  return toupper(ch)-'A';
}

bool isSomething(string property){
  char ch;
  cout << "is graph " << property << "(y or n)? "; 
  cin >> ch;
  return (ch == 'n') ? false : true;
}

void check_bound(int u,int v, int upper_bound){
  if(u >= upper_bound || v >= upper_bound){
    cout << "Out of Bound";
    exit(0);
  }
}

