#include <cmath>

#include "geometry.hpp"

mat4 mat4::operator+(const mat4& other) {
  mat4 result;
  for(int i = 0; i < 16; i++) {
    result[i] = mat[i] + other[i];
  }
  return result;
}

mat4 mat4::operator*(const mat4& other) {
  mat4 result;
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      for(int step = 0; step < 4; step++) {
        result[row*4 + col] += mat[row*4 + step] * other[step*4 + col];
      }
    }
  }
  return result;
}

mat4 mat4::Transform() {
  mat4 m;
  for(int i = 0; i < 16; i++) {
    if(i / 4 == i % 4) {
      m[i] = 1;
    } else {
      m[i] = 0;
    }
  }
  return m;
}

mat4 mat4::Translate(float x, float y, float z) {
  mat4 m = mat4::Transform();
  m[3] = x;
  m[7] = y;
  m[11] = z;
  return m * *this;
}

mat4 mat4::Scale(float factor) {
  mat4 m = mat4::Transform();
  m[0] = m[5] = m[10] = factor;
  m[15] = 1;
  return m * *this;
}

mat4 mat4::RotateZ(float alpha) {
  mat4 m = mat4::Transform();
  m[0] = cos(alpha);
  m[1] = -sin(alpha);
  m[4] = sin(alpha);
  m[5] = cos(alpha);
  return m * *this;
}

mat4 mat4::RotateY(float alpha) {
  mat4 m = mat4::Transform();
  m[0]  = cos(alpha);
  m[3]  = -sin(alpha);
  m[8]  = sin(alpha);
  m[10] = cos(alpha);
  return m * *this;
}

mat4 mat4::RotateX(float alpha) {
  mat4 m = mat4::Transform();
  m[5]  = cos(alpha);
  m[6]  = -sin(alpha);
  m[9]  = sin(alpha);
  m[10] = cos(alpha);
  return m * *this;
}

mat4 mat4::Transpose() {
  mat4 m;
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      m[row*4+col] = (*this)[col*4+row];
    }
  }
  return m;
}

std::ostream& operator<<(std::ostream &strm, const vec3 &v) {
  strm << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return strm;
}

std::ostream& operator<<(std::ostream &strm, const vec4 &v) {
  strm << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return strm;
}
