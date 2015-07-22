#ifndef AI_H
#define AI_H
#include "Util.h"
#include "GameManager.h"
class AI {
  private:
    GameManager* gm;
  public:
    AI(GameManager* gm);
    int think();
    double _search(int depth,GameManager _gm);
};

#endif
