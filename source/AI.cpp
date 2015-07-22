#include "AI.h"
AI::AI(GameManager* gm){
  this->gm = gm;
}

int AI::think(){
  double max_val,temp;
  int dir,cur_score;
  max_val = temp = 0;
  cur_score = gm->grid->cur_score();
  for(int i=0;i<4;i++){
    GameManager cp_gm = GameManager(*gm);
    cp_gm.move(i);
    temp = _search(1,cp_gm);
    if(temp > max_val&&cp_gm.grid->cur_score()!=cur_score){
      max_val = temp;
      dir = i;
    }
  }
  return dir;
}

// return score of search
double AI::_search(int depth,GameManager _gm){
  if(depth>5)return _gm.grid->score();
  double max_val = 0;
  for(int i=0;i<4;i++){
    GameManager cp_gm = _gm;
    cp_gm.move(i);
    max_val = max(_search(depth+1,cp_gm),max_val);
  }
  return max_val;
}
