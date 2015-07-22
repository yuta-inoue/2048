#include "GameManager.h"
#include "AI.h"
double colors[14][3] = {{0.733,0.678,0.627},{0.933f,0.894,0.855},{0.929,0.878,0.784},{0.949,0.694,0.475},{0.961,0.584,0.388},{0.965,0.486,0.373},{0.965,0.369,0.231},{0.929,0.812,0.447},{0.929,0.80,0.38},{0.929,0.784,0.314},{0.929,0.773,0.247},{0.929,0.761,0.18},{0.235,0.227,0.196}};
GameManager* gm;
int getPow(int n){
  for(int i=0;i<13;i++){
    if(pow(2,i)==n)return i;
  }
  return 0;
}
void display(){
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_QUADS);
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      int index = getPow(gm->grid->getVal(P(j,i)));
      glColor3f(colors[index][0],colors[index][1],colors[index][2]);
      glVertex2f(-1+0.5*i,1-0.5*j);
      glVertex2f(-1+0.5*(i+1),1-0.5*j);
      glVertex2f(-1+0.5*(i+1),1-0.5*(j+1));
      glVertex2f(-1+0.5*i,1-0.5*(j+1));
    }
  }
  glEnd();
  for(int i=0;i<4;i++){
    for(int j=0;j<4;j++){
      glColor3f(0,0,0);
      glRasterPos2f(-0.75+0.5*i,0.75-0.5*j);
      char buffer[10];
      int val = gm->grid->getVal(P(j,i));
      if(val!=0){
        sprintf(buffer,"%d",val);
        for(int i=0;i<strlen(buffer);i++){
          glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,buffer[i]);
        }
      }
    }
  }
  glFlush();
}

void init(){
  glClearColor(0.0,0.0,1.0,1.0);
}

void keyboard(unsigned char key, int x,int y){
  cout << key << endl;
  switch (key) {
    case 27:
      exit(0);
      break;
  }
}

void keySpecial(int key,int x,int y){
  cout << key << endl;
  switch (key) {
    case GLUT_KEY_LEFT:
      gm->move(0);
      break;
    case GLUT_KEY_RIGHT:
      gm->move(2);
      break;
    case GLUT_KEY_DOWN:
      gm->move(1);
      break;
    case GLUT_KEY_UP:
      gm->move(3);
      break;
  }
  display();
}

void reshape(int w,int h){

}

void aiStart(){
  float secs = 0.1;
  cout << "start ai" << endl;
  AI* ai = new AI(gm);
  int direction;
  while(!gm->isGameOver()){
    cout << "call ai" << endl;
    direction = ai->think();
    cout << direction << endl;
    gm->move(direction);
    display();
    float end = clock()/CLOCKS_PER_SEC + secs;
    while((clock()/CLOCKS_PER_SEC)<end);
  }
}

int main(int argc,char *argv[]){
  gm = new GameManager();
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA);
  glutCreateWindow("2048 AI");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keySpecial);
  glutIdleFunc(aiStart);
  glutMainLoop();
  return 0;
}
