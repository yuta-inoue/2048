#include "GameManager.h"

GameManager::GameManager(const GameManager& gm){
  grid = new Grid(gm.grid->field,gm.grid->merged);
  over = gm.over;
  score = gm.score;
}

GameManager::GameManager(){
  grid = new Grid();
  over = false;
  score = 0;

}

// 0:left, 1: down, 2: right, 3: up
void GameManager::move(int direction){
  if(over){
    cout << "Game Over";
    return;
  }
  P v = getVector(direction);
  bool moved = false;
  initTraversals(v);
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      if(!grid->isAvailable(P(dx[i],dy[j]))){
        map<string,P> positions = grid->findFarthestPosition(P(dx[i],dy[j]),v);
        P next = positions["next"];
        if(isValid(next)&&grid->getVal(next)==grid->getVal(P(dx[i],dy[j]))&&!grid->isMerged(next)){
          grid->merge(P(dx[i],dy[j]),next);
          moved = true;
        } else {
          if(!(dx[i]==positions["farthest"].first&&dy[j]==positions["farthest"].second)){
            grid->moveTile(P(dx[i],dy[j]),positions["farthest"]);
            moved = true;
          }
        }
      }
    }
  }
  if(moved){
    grid->addRandomTile();
    if(!grid->movesAvailable()){
      over = true;
    }
  }
  grid->update();
}

void GameManager::initTraversals(P v){
  for(int i=0;i<4;i++)dx[i]=i,dy[i]=i;
  if(v.first==1)sort(dx,dx+4,greater<int>());
  if(v.second==1)sort(dy,dy+4,greater<int>());
}

bool GameManager::isGameOver(){
  return over;
}
