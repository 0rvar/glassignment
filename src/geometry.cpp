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

std::ostream& operator<<(std::ostream &strm, const vec3 &v) {
  strm << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
  return strm;
}

std::ostream& operator<<(std::ostream &strm, const vec4 &v) {
  strm << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return strm;
}
