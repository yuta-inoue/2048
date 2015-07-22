#include "Util.h"

bool isValid(P pos){
  return (0<=pos.first&&pos.first<FIELD_SIZE&&0<=pos.second&&pos.second<FIELD_SIZE);
}

P getVector(int direction){
  vector<P> dir;
  dir.push_back(P(0,-1));
  dir.push_back(P(1,0));
  dir.push_back(P(0,1));
  dir.push_back(P(-1,0));
  return dir[direction];
}

void printV(P v){
  cout << endl;
  cout << v.first << " " << v.second << endl;
}
