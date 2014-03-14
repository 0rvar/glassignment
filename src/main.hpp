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
#include "state.hpp"
#include "guicontrol.hpp"

#include "timer.hpp"

void renderScene();
void loadModel(model::data m);
void idle();

void onMouseMove(int x, int y);
void onPassiveMouseMove(int x, int y);
void onMouse(int button, int state, int x, int y);
void onKeyDown(unsigned char, int, int);
void onKeyUp(unsigned char, int, int);
void onSpecialDown(int, int, int);
void reshape(int width, int height);

void loadModelFile(char* filename);
void reset();
void setOrthographic();
void setOblique();
void setPerspective();
void setPerspective(const float &far, const float &near, const float &fov);

void initGlut(int, char**);
void initGL();
void initGUI();

#endif  /* MAIN_HPP */