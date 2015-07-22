#ifndef GRID_H
#define GRID_H
#include "Util.h"
#include "Tile.h"
class Grid {
  private:
    //Tile grid[FIELD_SIZE][FIELD_SIZE];
  public:
    int field[FIELD_SIZE][FIELD_SIZE];
    bool merged[FIELD_SIZE][FIELD_SIZE];
    Grid();
    Grid(int _field[4][4],bool _merged[4][4]);
    int cur_score();
    double score();
    double smoothness();
    double monotonicity();
    void disp();
    bool isAvailable(P pos);
    bool isMerged(P pos);
    int getVal(P pos);
    bool isGameTerminated();
    void addRandomTile();
    void moveTile(P from, P to);
    bool movesAvailable();
    void merge(P from,P to);
    vector<P> availableCells();
    P randomAvailableCell();
    map<string,P> findFarthestPosition(P cell,P v);
    void update();
};
#endif
