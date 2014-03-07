#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtk/gtk.h>
#include <cmath>

#include "geometry.hpp"
#include "off.hpp"
#include "shadertools.hpp"

#include "timer.hpp"

void loadVertices(std::vector<vec3>);
void idle();
void onKeyDown(unsigned char, int, int);
void onSpecialDown(int, int, int);
void renderScene();
void loadVertices(std::vector<vec3>);
void initGlut(int, char**);
void initGL();
void reshape();

void initGuiWindow(const char*);
void guiInit(int *, char**);
void guiMainIteration(void);
void gui_atclose();

void setOrthographic();
void setOblique();
void setPerspective();

#define PI 3.141592f
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define STATE_IDLE 0
#define STATE_OPEN 1
#define STATE_TRANSLATE 2
#define STATE_SCALE 3
#define STATE_ROTATE 4
#define SUBSTATE_TRANSLATE_X 0
#define SUBSTATE_TRANSLATE_Y 1
typedef struct S {
  bool shouldUpdate;
  float dx, dy, s, az;
  int current, sub;
  S() : shouldUpdate(false),dx(0),dy(0),s(1),az(0),current(0),sub(0) {}
} ControlState;
ControlState state;

GLuint    idTransMat;
GLuint    idViewMat;
GLuint    idProjMat;

uint      vertexCount = 0;
vec3      p0 = vec3(2, 0, 2);
vec3      pref = vec3(0, 0, 0);
vec3      V = vec3(0, 1, 0);

mat4      view = createViewMatrix(p0, pref, V);
mat4      transform = mat4::Identity();
mat4      projection = mat4::Identity();

#define glsl(x) "#version 140\n" #x
const char* vertex_shader = glsl(
  in vec3 vPosition;

  uniform mat4 T;
  uniform mat4 V;
  uniform mat4 P;

  void main() {
    gl_Position =  P*V*T*vec4(vPosition, 1.0);
  }
);
const char* fragment_shader = glsl(
  out vec4 fColor;

  void main() {
    fColor = vec4( 1.0, 0.0, 0.0, 1.0 );
  }
);




void idle() {
  guiMainIteration();
  
  if(!state.shouldUpdate) {
    return;
  }

  if(state.current == STATE_OPEN) {
    std::string filename;
    std::vector<vec3> vertices;

    std::cout << "Enter filename: ";
    std::cin >> filename;

    try {
      vertices = OFF::read(filename.c_str());
      loadVertices(vertices);
    } catch(OFF::ParseException &e) {
      std::cerr << "Invalid OFF-file: \"" << e.what() << "\" on line " << e.line << std::endl;
    }
    state.current = STATE_IDLE;
  } else {
    std::cout << "Updating transform" << std::endl;
    transform = mat4::Identity()
      .RotateZ(state.az)
      .Scale(state.s)
      .Translate(state.dx, state.dy, 0);
  }

  state.shouldUpdate = false;

  glutPostRedisplay();
}

void onKeyDown(unsigned char key, int x, int y){
  if(key == 'o') {
    state.current = STATE_OPEN;
  } else if(key == 't') {
    state.current = STATE_TRANSLATE;
    state.sub = SUBSTATE_TRANSLATE_X;
    std::cout << "Entering translate mode for X" << std::endl;
  } else if(key == 's') {
    state.current = STATE_SCALE;
    std::cout << "Entering scale mode" << std::endl;
  } else if(key == 'r') {
    state.current = STATE_ROTATE;
    std::cout << "Entering rotate mode around Z" << std::endl;
  } else if(key == 'x' || key == 'y') {
    if(state.current == STATE_TRANSLATE) {
      if(key == 'x') {
        state.sub = SUBSTATE_TRANSLATE_X;
        std::cout << "Entering translate mode for X" << std::endl;
      } else if(key == 'y') {
        state.sub = SUBSTATE_TRANSLATE_Y;
        std::cout << "Entering translate mode for Y" << std::endl;
      }
    }
  } else if(key == '+' || key == '-') {
    float sign = -1.0; float diff;
    if(key == '+') { sign = 1.0; }

    switch(state.current) {
    case STATE_TRANSLATE:
      diff = 0.1 * sign;
      if(state.sub == SUBSTATE_TRANSLATE_X) {
        state.dx += diff;
      } else {
        state.dy += diff;
      }
      break;  
    case STATE_SCALE:
      diff = 0.1 * sign;
      state.s += diff;
      break;
    case STATE_ROTATE:
      diff = 3.141592/36 * sign;
      state.az += diff;
    }
  } else {
    return;
  }
  
  std::cout.flush();
  state.shouldUpdate = true;
}

void onSpecialDown(int key, int x, int y) {
  int mod = glutGetModifiers();

  if(mod & GLUT_ACTIVE_SHIFT) {
    switch(key) {
    case GLUT_KEY_UP:
      state.s += 0.1;
      break;
    case GLUT_KEY_DOWN:
      state.s -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      state.az -= 3.141592/36;
      break;
    case GLUT_KEY_LEFT:
      state.az += 3.141592/36;
      break;
    default:
      return;
    }
  } else {
    switch(key) {
    case GLUT_KEY_UP:
      state.dy += 0.1;
      break;
    case GLUT_KEY_DOWN:
      state.dy -= 0.1;
      break;
    case GLUT_KEY_RIGHT:
      state.dx += 0.1;
      break;
    case GLUT_KEY_LEFT:
      state.dx -= 0.1;
      break;
    default:
      return;
    }
  }

  state.shouldUpdate = true;
}

void renderScene() {
  glUniformMatrix4fv(idTransMat, 1, GL_TRUE,
            (const float*)&transform);
  glUniformMatrix4fv(idViewMat, 1, GL_TRUE,
            (const float*)&view);
  glUniformMatrix4fv(idProjMat, 1, GL_TRUE,
            (const float*)&projection);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  glutSwapBuffers();

  std::cout << "dx: " << state.dx << ", " \
            << "dy: " << state.dy << ", " \
            << "s: "  << state.s  << ", " \
            << "az: " << state.az << std::endl;
}

void loadVertices(std::vector<vec3> vertices) {
  vec3 buf[vertices.size()];
  for(uint i = 0; i < vertices.size(); i++) {
    buf[i] = vertices[i];
  }
  vertexCount = vertices.size();

  /* Load it to the buffer data array */
  glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW );
}

void initGlut(int argc, char **argv) {
  /* Initialize glut */
  glutInit(&argc, argv);

  /* Display Mode 
      GLUT_DOUBLE together with glutSwapBuffers(); for double buffering */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
  /* Window Size */
  glutInitWindowSize(300, 300);
  glutInitContextProfile( GLUT_CORE_PROFILE );
  /* GL Version 
     Check with glxinfo | grep Open for supported version */
  glutInitContextVersion(3, 1);    

  /* Window label */
  glutCreateWindow("Assignment 1");
}


void initGL(void) {
  GLuint program;
  GLuint buffer;
  GLuint loc;
  GLuint vao;

  /* Setting up GL Extensions */
  glewExperimental = GL_TRUE; 
  glewInit();

  /* Create and initialize a program object with shaders */
  program = Shading::initProgram(vertex_shader, fragment_shader);

  /* installs the program object as part of current rendering state */
  glUseProgram(program);

  /* Creat a vertex array object */ 
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  /* Create buffer in the shared display list space and 
     bind it as GL_ARRAY_BUFFER */
  glGenBuffers( 1, &buffer);
  glBindBuffer( GL_ARRAY_BUFFER, buffer);
  
  /* Initialize attribute vPosition in program */
  loc = glGetAttribLocation( program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)BUFFER_OFFSET(0));

  idTransMat = glGetUniformLocation(program, "T");
  idViewMat  = glGetUniformLocation(program, "V");
  idProjMat  = glGetUniformLocation(program, "P");

  /* Set graphics attributes */
  glLineWidth(1.0);
  glPointSize(1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshape(int width, int height) {
  int size = std::min(width, height);
  int x_off = (width-size)/2;
  int y_off = (height-size)/2;
  glViewport(x_off, y_off, size, size);
}

int main(int argc, char *argv[]) {
  for(int i = 0; i < 16; i++) {
    std::cout << view[i] << ", ";
  }
  std::cout << std::endl;

  /* Initialization */
  initGlut(argc, argv);
  initGL();

  glutDisplayFunc(renderScene);
  glutIdleFunc(idle);
  glutKeyboardFunc(onKeyDown); //glutKeyboardUpFunc(onKeyUp);
  glutSpecialFunc(onSpecialDown);
  glutReshapeFunc(reshape);

  if(argc > 1) {
    try {
      std::vector<vec3> vertices = OFF::read(argv[1]);
      loadVertices(vertices);
    } catch(OFF::ParseException &e) {
      std::cerr << "Invalid OFF-file: \"" << e.what() << "\" on line " << e.line << std::endl;
    }
  }

  /* Initialize GUI */
  //guiInit(&argc, argv);
  //initGuiWindow("ass2gui.glade");

  /* Set up exit function */
  //atexit(&gui_atclose);

  setOrthographic();
  state.shouldUpdate = true;

  /* Loop for a short while */
  glutMainLoop();

  return 0;
}

void setOrthographic() {
  float left,right,top,bottom,far,near;
  right = top = near = 5;
  left = bottom = far = -5;

  mat4 ST = mat4::Identity()
      .Translate(-(left+right)/(right-left), -(top+bottom)/(top-bottom), -(far+near)/(far-near))
      .Scale(2.0f/(right-left), 2.0f/(top-bottom), 2.0f/(far-near));

  projection = ST;
}

void setOblique() {
  float theta, psi;
  theta = psi = PI/4;

  mat4 H = mat4::Identity();
  H[2] = cos(theta)/sin(theta);
  H[6] = cos(psi)/sin(psi);

  setOrthographic();
  projection = projection * H;
}

void setPerspective() {
  float left,right,top,bottom,far,near;
  right = top = near = 5;
  left = bottom = far = -5;
  mat4 P;

  P[0] = 2*near/(right-left);
  P[5] = 2*near/(top-bottom);
  P[2] = (right+left)/(right-left);
  P[6] = (top+bottom)/(top-bottom);
  P[10] = -(far+near)/(far-near);
  P[11] = -(2*far*near)/(far-near);
  P[14] = -1;

  projection = P;
}


void gui_atclose() {
  std::cout << "Wut";
}
