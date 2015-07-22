#ifndef TILE_H
#define TILE_H
#include "Util.h"
class Tile {
  private:
    int x,y,value;
  public:
    Tile(int x,int y, int value);
    void updatePos(int x,int y);
};
#endif
