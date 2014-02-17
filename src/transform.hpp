/* 
 * File:   Transform.hpp
 * Author: orvar
 *
 * Created on 05 February 2014, 09:43
 */

#include "geometry.hpp"

#ifndef TRANSFORM_HPP
#define	TRANSFORM_HPP

class Transform {
public:
  Transform();
  Transform Translate(float x, float y, float z);
  Transform Scale(float factor);
  Transform RotateZ(float alpha);
  Transform RotateY(float alpha);
  Transform RotateX(float alpha);
  mat4 GetMatrix();
  Transform Transpose();
private:
  
  mat4 matrix;
};

#endif	/* TRANSFORM_HPP */

