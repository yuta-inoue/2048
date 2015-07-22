#include "Grid.h"
int ax[4] = {-1,0,1,0};
int ay[4] = {0,-1,0,1};

Grid::Grid(int _field[4][4],bool _merged[4][4]){
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      field[x][y] = _field[x][y];
      merged[x][y] = _merged[x][y];
    }
  }
}

Grid::Grid(){
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      field[x][y] = 0;
      merged[x][y] = false;
    }
  }
  addRandomTile();
}

int Grid::cur_score(){
  int score = 0;
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      score += field[x][y];
    }
  }
  return score;
}

double Grid::score(){
  int max_val,empty_cell_num;
  empty_cell_num = 0;
  max_val = 0;
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      if(field[x][y]==0)empty_cell_num++;
      max_val = max(max_val,field[x][y]);
    }
  }
  return smoothness()*0.1 + monotonicity()*1.0 + log(empty_cell_num) * 2.7 + max_val * 1.0;
}

double Grid::smoothness(){
  double smoothness = 0;
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      if(field[x][y]!=0){
        int val = (int)(log(field[x][y])/log(2));
        for(int i=2;i<4;i++){
          map<string,P> mp = findFarthestPosition(P(x,y),P(x+ax[i],y+ay[i]));
          P cell = mp["next"];
          if(field[cell.first][cell.second]!=0){
            smoothness -= abs(val - (int)(log(field[cell.first][cell.second])/log(2)));
          }
        }
      }
    }
  }
  return smoothness;
}

double Grid::monotonicity(){
  int total[4] = {};
  for(int x=0;x<FIELD_SIZE;x++){
    int cur = 0;
    int next = cur + 1;
    while(next < FIELD_SIZE){
      while(next < FIELD_SIZE && field[x][next]!=0){
        next++;
      }
      if(next>=4)next--;
      int cur_val = (field[x][cur]!=0) ? (int)(log(field[x][cur])/log(2)) : 0;
      int next_val = (field[x][next]!=0) ? (int)(log(field[x][next])/log(2)) : 0;
      if(cur_val > next_val){
        total[0] += next_val - cur_val;
      } else if(cur_val < next_val){
        total[1] += cur_val - next_val;
      }
      cur = next;
      next++;
    }
  }

  for(int y=0;y<FIELD_SIZE;y++){
    int cur=0;
    int next = cur+1;
    while(next < FIELD_SIZE){
      while(next < FIELD_SIZE && field[next][y]!=0){
        next++;
      }
      if(next>=FIELD_SIZE)next--;
      int cur_val = (field[cur][y]!=0) ? (int)(log(field[cur][y])/log(2)) : 0;
      int next_val = (field[next][y]!=0) ? (int)(log(field[next][y])/log(2)) : 0;
      if(cur_val > next_val){
        total[2] += next_val - cur_val;
      } else if(cur_val < next_val){
        total[3] += cur_val - next_val;
      }
      cur = next;
      next++;
    }
  }
  return max(total[0],total[1]) + max(total[2],total[3]);
}

void Grid::disp(){
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      cout << field[x][y] << " ";
    }
    cout << endl;
  }
}

void Grid::update(){
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      merged[i][j]=false;
    }
  }
}

bool Grid::isAvailable(P pos){
  return field[pos.first][pos.second]==0;
}

bool Grid::isMerged(P pos){
  return merged[pos.first][pos.second];
}

void Grid::merge(P from,P to){
  field[to.first][to.second] = field[from.first][from.second] * 2;
  field[from.first][from.second] = 0;
  merged[to.first][to.second] = true;
}

P Grid::randomAvailableCell(){
  vector<P> v = availableCells();
  return v[rand() % v.size()];
}

vector<P> Grid::availableCells(){
  vector<P> v;
  for(int x=0;x<FIELD_SIZE;x++){
    for(int y=0;y<FIELD_SIZE;y++){
      if(field[x][y]==0)v.push_back(P(x,y));
    }
  }
  return v;
}

void Grid::addRandomTile(){
  P pos = randomAvailableCell();
  int val;
  if(rand() % 100 > 90){
    val = 4;
  } else {
    val = 2;
  }
  field[pos.first][pos.second] = val;
}

bool Grid::movesAvailable(){
  int nx,ny;
  vector<P> positions = availableCells();
  if(positions.size()>0)return true;
  for(int x=0;x<4;x++){
    for(int y=0;y<4;y++){
      for(int i=0;i<4;i++){
        nx = x + ax[i],ny = y + ay[i];
        if(isValid(P(nx,ny))){
          if(field[nx][ny]==field[x][y])return true;
        }
      }
    }
  }
  return false;
}

map<string,P> Grid::findFarthestPosition(P cell,P v){
  P p;
  map<string,P> m;
  do {
    p = cell;
    cell = P(p.first + v.first,p.second + v.second);
  } while(isValid(cell)&&isAvailable(cell));
  m["farthest"] = p;
  m["next"] = cell;
  return m;
}

int Grid::getVal(P pos){
  return field[pos.first][pos.second];
}

void Grid::moveTile(P from,P to){
  field[to.first][to.second] = field[from.first][from.second];
  field[from.first][from.second] = 0;
}
