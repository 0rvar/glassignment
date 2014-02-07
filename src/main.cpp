#include <GL/glut.h>

#include <iostream>
#include <string>
#include <vector>

#include "vertex.hpp"
#include "off.hpp"

#include "timer.hpp"

using namespace std;

bool init() {

  return true;
}

vector<Vertex*> polygons;
void renderScene() {
  Timer t = Timer("renderScene"); //DEBUG
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glLoadMatrixf(mat44);

  glBegin(GL_TRIANGLES);
    for(vector<Vertex*>::iterator it = polygons.begin(); it != polygons.end(); ++it) {
      Vertex* v = *it;
      glVertex3f(v->x, v->y, v->z);
    }
  glEnd();

  glutSwapBuffers();

  t.Report(); //DEBUG
}

void idle() {
  // Animation Code

  // Use this function to trigger a redisplay
  //glutPostRedisplay();
}


void onKeyDown(unsigned char key, int x, int y){
  cout  << "Pressed key : " << (char)key 
        << " (" << (int)key << ") "
        << " at position : ("
        << x << "," << y << ")" << endl;

  int mod = glutGetModifiers();
  switch(mod) {
  case GLUT_ACTIVE_CTRL:
    cout << "Ctrl Held" << endl; break;
  case GLUT_ACTIVE_SHIFT:
    cout << "Shift Held" << endl; break;
  case GLUT_ACTIVE_ALT:
    cout << "Alt Held" << endl; break;
  }
}

void onSKeyDown(int key, int x, int y) {
  //GLUT_KEY_UP, GLUT_GET_DOWN etc
}

int main(int argc, char *argv[]) {

  if(argc < 2) {
      cerr << "Invalid usage, please pass in OFF-file as first argument";
      return 1;
  }
  
  Timer t = Timer("readOFF"); //DEBUG

  polygons = readOFF(argv[1]);

  t.Report(); //DEBUG
  
  t.Restart("glut initialization"); //DEBUG

  glutInit(&argc, argv);
  
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);

  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

  glutCreateWindow("Assignment 1");

  glutDisplayFunc(renderScene);
  glutIdleFunc(idle);

  glutKeyboardFunc(onKeyDown);
  //glutKeyboardUpFunc(onKeyUp);
  glutSpecialFunc(onSKeyDown);

  if (!init()) {
    return 1;
  }

  t.Report(); //DEBUG

  glutMainLoop();

  return 0;
}
