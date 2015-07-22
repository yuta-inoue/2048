#include "Tile.h"

Tile::Tile(int x,int y,int value){
  this->x = x;
  this->y = y;
  this->value = value ? value : 2;
}

void Tile::updatePos(int x,int y){
  this->x = x;
  this->y = y;
}
