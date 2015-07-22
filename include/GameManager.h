#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include "Util.h"
#include "Grid.h"
class GameManager {
  private:
    bool over;
    int score;
    int dx[4],dy[4];
  public:
    Grid* grid;
    GameManager();
    GameManager(const GameManager& gm);
    void move(int direction);
    void initTraversals(P v);
    bool isGameOver();
};
#endif
