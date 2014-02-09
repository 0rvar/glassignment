#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "vertex.hpp"
#include "off.hpp"
#include "shadertools.hpp"
#include "transform.hpp"

#include "timer.hpp"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
uint      vertexCount;
Transform transform;

void renderScene() {
  Timer t = Timer("renderScene"); //DEBUG

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
  glutSwapBuffers();

  t.Report(); //DEBUG
}

void idle() {
  // Animation Code

  // Use this function to trigger a redisplay
  //glutPostRedisplay();
}

void loadVertices(std::vector<Vertex> vertices) {
  Vertex buf[vertices.size()];
  for(uint i = 0; i < vertices.size(); i++) {
    buf[i] = vertices[i];
  }
  vertexCount = vertices.size();

  /* Load it to the buffer data array */
  glBufferData(GL_ARRAY_BUFFER, sizeof(buf), buf, GL_STATIC_DRAW );
}

void onKeyDown(unsigned char key, int x, int y){
  std::cout  << "Pressed key : " << (char)key 
        << " (" << (int)key << ") "
        << " at position : ("
        << x << "," << y << ")" << std::endl;

  int mod = glutGetModifiers();
  switch(mod) {
  case GLUT_ACTIVE_CTRL:
    std::cout << "Ctrl Held" << std::endl; break;
  case GLUT_ACTIVE_SHIFT:
    std::cout << "Shift Held" << std::endl; break;
  case GLUT_ACTIVE_ALT:
    std::cout << "Alt Held" << std::endl; break;
  }
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
  GLuint idTransMat;

  /* Setting up GL Extensions */
  glewExperimental = GL_TRUE; 
  glewInit();

  /* Create and initialize a program object with shaders */
  program = initProgram("vshader.glsl", "fshader.glsl");

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
  glUniformMatrix4fv(idTransMat, 1, GL_FALSE,
            (const float*)&transform);

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
  std::vector<Vertex> vertices;
  if(argc < 2) {
      std::cerr << "Invalid usage, please pass in OFF-file as first argument";
      return 1;
  }

  transform = transform
    .Translate(100, 0, 0)
    .Scale(0.008)
    .Transpose(); // the model-view matrix is transposed for some kinky reason
  
  Timer t = Timer("readOFF()"); //DEBUG

  try {
    vertices = readOFF(argv[1]);
  } catch(OFFParseException &e) {
    std::cerr << "Invalid OFF-file: \"" << e.what() << "\" on line " << e.line << std::endl;
    return 1;
  }
  
  t.Report(); //DEBUG
  t.Restart("OpenGL initialization"); //DEBUG

  /* Initialization */
  initGlut(argc, argv);
  initGL();

  t.Report(); //DEBUG

  t.Restart("loadVertices"); //DEBUG
  loadVertices(vertices);
  t.Report(); //DEBUG

  glutDisplayFunc(renderScene);
  glutIdleFunc(idle);
  glutKeyboardFunc(onKeyDown); //glutKeyboardUpFunc(onKeyUp);
  glutReshapeFunc(reshape);

  /* Loop for a short while */
  glutMainLoop();

  return 0;
}
