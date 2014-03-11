#ifndef MAIN_HPP
#define MAIN_HPP

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <gtk/gtk.h>
#include <cmath>

#include "geometry.hpp"
#include "model.hpp"
#include "shadertools.hpp"
#include "camera.hpp"

#include "timer.hpp"

#define PI 3.141592f
#define BUFFER_SIZE 3000
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define CAMERA_SPEED 0.03
#define MOUSE_SENSITIVITY 0.005

typedef struct S {
  bool shouldUpdate;
  struct transform_ {
    float dx, dy, s, ax, ay, az;
    transform_():
        dx(0),
        dy(0),
        s(1),
        ax(0),
        ay(0),
        az(0) {};
  } transform;
  struct heldkeys_ {
    bool w,a,s,d,q,e,shift,space;
  } heldkeys;
  struct mouse_ {
    int last_x, last_y;
    float horizontal_rotation, vertical_rotation;
  } mouse;
  int window_width, window_height;
  struct render_ {
    uint num_indices;
  } render;
  S(): shouldUpdate(false), heldkeys({0}), mouse({0}) {};
} ControlState;
ControlState state;

GLuint    locPosition;
GLuint    locNormal;
GLuint    idTransMat;
GLuint    idViewMat;
GLuint    idProjMat;

vec3      p0 = vec3(0, 0, 3);
vec3      pref = vec3(0, 0, 2);
vec3      up = vec3(0, 1, 0);

camera    cam = camera(p0, pref, up);
mat4      transform = mat4::Identity();
mat4      projection = mat4::Identity();

void renderScene();
void loadModel(model::data m);
void idle();

void onMouseMove(int x, int y);
void onKeyDown(unsigned char, int, int);
void onKeyUp(unsigned char, int, int);
void onSpecialDown(int, int, int);
void reshape(int width, int height);

void setOrthographic();
void setOblique();
void setPerspective(const float &far, const float &near, const float &fov);

void initGlut(int, char**);
void initGL();

#endif  /* MAIN_HPP */