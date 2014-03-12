#include <cmath>

#include "geometry.hpp"

vec3 vec3::operator-(const vec3& b) {
  vec3 r, a = (*this);
  r.x =  a.x - b.x;
  r.y =  a.y - b.y;
  r.z =  a.z - b.z;
  return r;
}

vec3 vec3::operator+(const vec3& b) {
  vec3 r, a = (*this);
  r.x =  a.x + b.x;
  r.y =  a.y + b.y;
  r.z =  a.z + b.z;
  return r;
}

vec3 vec3::operator*(const float factor) {
  vec3 r = (*this);
  r.x *= factor;
  r.y *= factor;
  r.z *= factor;
  return r;
}

vec3 vec3::cross(vec3 b) {
  vec3 r, a = (*this);
  r.x =  (a.y * b.z) - (b.y * a.z);
  r.y = -(a.x * b.z) + (b.x * a.z);
  r.z =  (a.x * b.y) - (a.y * b.x);
  return r;
}

float vec3::dot(const vec3 &b) {
  float r;
  vec3 a = (*this);
  r = a.x * b.x + a.y * b.y + a.z * b.z;
  return r;
}


vec3 vec3::normalize() {
  return (*this) * (1.0f/this->length());
}

float vec3::length() {
  float x = this->x;
  float y = this->y;
  float z = this->z;
  return sqrt(x*x + y*y + z*z);
}

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

vec3 mat4::operator*(const vec3& other) {
  vec3 result;
  
  result.x += mat[0*4 + 0] * other.x;
  result.x += mat[0*4 + 1] * other.y;
  result.x += mat[0*4 + 2] * other.z;
  result.x += mat[0*4 + 3] * 1;

  result.y += mat[1*4 + 0] * other.x;
  result.y += mat[1*4 + 1] * other.y;
  result.y += mat[1*4 + 2] * other.z;
  result.y += mat[1*4 + 3] * 1;

  result.z += mat[2*4 + 0] * other.x;
  result.z += mat[2*4 + 1] * other.y;
  result.z += mat[2*4 + 2] * other.z;
  result.z += mat[2*4 + 3] * 1;

  return result;
}

mat4 mat4::Identity() {
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
  mat4 m = mat4::Identity();
  m[3] = x;
  m[7] = y;
  m[11] = z;
  return m * (*this);
}

mat4 mat4::Translate(vec3 v) {
  return this->Translate(v.x, v.y, v.z);
}

mat4 mat4::Scale(float factor) {
  mat4 m = mat4::Identity();
  m[0] = m[5] = m[10] = factor;
  m[15] = 1;
  return m * (*this);
}

mat4 mat4::Scale(float x_factor, float y_factor, float z_factor) {
  mat4 m = mat4::Identity();
  m[0]  = x_factor;
  m[5]  = y_factor;
  m[10] = z_factor;
  m[15] = 1;
  return m * (*this);
}

mat4 mat4::RotateZ(float alpha) {
  mat4 m = mat4::Identity();
  m[0] = cos(alpha);
  m[1] = -sin(alpha);
  m[4] = sin(alpha);
  m[5] = cos(alpha);
  return m * *this;
}

mat4 mat4::RotateY(float alpha) {
  mat4 m = mat4::Identity();
  m[0]  = cos(alpha);
  m[2]  = -sin(alpha);
  m[8]  = sin(alpha);
  m[10] = cos(alpha);
  return m * *this;
}

mat4 mat4::RotateX(float alpha) {
  mat4 m = mat4::Identity();
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

std::ostream& operator<<(std::ostream &strm, const mat4 &m) {
  strm << "mat4 =";
  for(int i = 0; i < 16; i++) {
    if(i % 4 == 0) {
      strm << std::endl << "\t";
    }
    strm << m[i] << " ";
  }
  strm << std::endl;
  return strm;
}
