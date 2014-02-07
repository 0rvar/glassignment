/* 
 * File:   Transform.cpp
 * Author: orvar
 * 
 * Created on 05 February 2014, 09:43
 */

#include "transform.hpp"

Transform::Transform() {
  for(int i = 0; i < 16; i++) {
    if(i / 4 == i % 4) {
      mat[i] = 1;
    } else {
      mat[i] = 0;
    }
  }
}

Transform* Transform::Translate(float x, float y, float z) {
  
  
  return this;
}

float* Transform::GetMatrix() {
  return mat;
}
