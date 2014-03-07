#include <ostream>

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

class vec3 {
public:
  float x, y, z;
  vec3(): x(0),y(0),z(0) {};
  vec3(float _x, float _y, float _z): x(_x), y(_y), z(_z) {};

  vec3 operator-(const vec3& other);
  vec3 operator+(const vec3& other);
  vec3 operator*(const float factor);
  vec3 cross(vec3 other);
  vec3 normalize();
  float length();
};

class vec4 {
public:
  float x, y, z, w;
  vec4(): x(0),y(0),z(0),w(1) {};
  vec4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {};
  vec4(float _x, float _y, float _z): x(_x), y(_y), z(_z), w(1) {};
};
class point4 {
public:
  float x, y, z, w;
  point4(): x(0),y(0),z(0),w(0) {};
  point4(float _x, float _y, float _z, float _w): x(_x), y(_y), z(_z), w(_w) {};
  point4(float _x, float _y, float _z): x(_x), y(_y), z(_z), w(0) {};
};

class mat4 {
public:
    mat4() {};
    float& operator[](unsigned int i){ return mat[i];}
    const float& operator[](unsigned int i)const{ return mat[i];}

    mat4 operator+(const mat4& other);
    mat4 operator*(const mat4& other);
    vec3 operator*(const vec3& other);
    mat4 Transpose();

    static mat4 Identity();
    mat4 Translate(float x, float y, float z);
    mat4 Translate(vec3 v);
    mat4 Scale(float factor);
    mat4 Scale(float x_factor, float y_factor, float z_factor);
    mat4 RotateZ(float alpha);
    mat4 RotateY(float alpha);
    mat4 RotateX(float alpha);
private:
    float mat[16] = {0};
};

std::ostream& operator<<(std::ostream &strm, const vec3 &v);
std::ostream& operator<<(std::ostream &strm, const vec4 &v);

#endif  /* GEOMETRY_HPP */