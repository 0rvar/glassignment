#ifndef STATE_
#define STATE_

#include "model.hpp"
#include "geometry.hpp"

typedef struct S {
  bool shouldUpdate, shouldReload;
  int window_width, window_height;
  char* newModelFilename;

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
  
  struct render_ {
    uint num_indices;
    model::data model;
    bool flip_normals;
  } render;

  struct lighting_ {
    vec3 light_position;
    vec4 light_intensity;
    vec4 ambient_intensity;
    vec4 material_ambient;
    vec4 material_diffuse;
    vec4 material_specular;
    uint phong;
  } lighting;

  S(): 
    shouldUpdate(false), 
    shouldReload(false),
    newModelFilename(NULL),
    heldkeys({0}), 
    mouse({0}) {};
} State;


#endif  /* STATE_HPP */
