#include <iostream>
#include <iomanip>

#include "camera.hpp"
#include "geometry.hpp"

camera::camera() {
  vec3 p0 = vec3(2, 0, 2);
  vec3 pref = vec3(0, 0, 0);
  vec3 up = vec3(0, 1, 0);
  MoveTo(p0, pref, up);
}

camera::camera(vec3 p0, vec3 pref, vec3 up) {
  MoveTo(p0, pref, up);
}

void camera::MoveTo(vec3 p0, vec3 pref, vec3 up) {
  vec3 n = (p0 - pref).normalize();
  vec3 u = up.cross(n).normalize();
  vec3 v = n.cross(u);

  mat4 M;
  M[0]  = u.x;
  M[1]  = u.y;
  M[2]  = u.z;
  M[4]  = v.x;
  M[5]  = v.y;
  M[6]  = v.z;
  M[8]  = n.x;
  M[9]  = n.y;
  M[10] = n.z;
  M[15] = 1;
  mat4 M_inv = M.Transpose();

  mat4 T      = mat4::Identity().Translate(vec3(0, 0, 0) - p0);
  mat4 T_inv  = mat4::Identity().Translate(p0);

  // Create new view and create inverse view for 
  //  later delta calculations
  view          = M * T;
  view_inverse  = T_inv * M_inv;

  // Cache camera for parametric curving
  cached_p0 = p0;
  cached_pref = pref;
  cached_up = up;
}

mat4* camera::GetView() {
  return &view;
}

void camera::Strafe(float delta) {
  vec3 p0   = view_inverse * vec3(delta, 0, 0);
  vec3 pref = view_inverse * vec3(delta, 0, -1);
  MoveTo(p0, pref, cached_up);
}

void camera::Drive(float delta) {
  vec3 p0   = view_inverse * vec3(0, 0, delta);
  vec3 pref = view_inverse * vec3(0, 0, delta-1);
  MoveTo(p0, pref, cached_up);
}

void camera::Elevate(float delta) {
  vec3 p0   = view_inverse * vec3(0, delta, 0);
  vec3 pref = view_inverse * vec3(0, delta, -1);
  MoveTo(p0, pref, cached_up);
}

void camera::RotateY(float alpha) {
  vec3 pref = view_inverse * mat4::Identity().RotateY(alpha) * vec3(0, 0, -1);
  MoveTo(cached_p0, pref, cached_up);
}

void camera::RotateX(float alpha) {
  vec3 pref = view_inverse * mat4::Identity().RotateX(alpha) * vec3(0, 0, -1);
  MoveTo(cached_p0, pref, cached_up);
}

void camera::SetAngles(float horizontal_angle, float vertical_angle) {
  vec3 pref = cached_p0 + vec3(0, 0, -1);
  MoveTo(cached_p0, pref, cached_up);
  mat4 rotate = mat4::Identity().RotateY(horizontal_angle).RotateX(vertical_angle);
  pref = view_inverse * rotate * vec3(0, 0, -1);
  MoveTo(cached_p0, pref, cached_up);
}

// Debugging
std::ostream& operator<<(std::ostream &strm, const camera &cam) {
  ((camera)cam).stream(strm);
  return strm;
}
void camera::stream(std::ostream &strm) {
  strm  << std::setprecision(3)
        << "cam =" << std::endl
        << "\tp0:   " << cached_p0   << std::endl
        << "\tpref: " << cached_pref << std::endl
        << "\tup:   " << cached_up   << std::endl;
  strm << "view_" << view;
}
