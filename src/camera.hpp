#include <ostream>

#include "geometry.hpp"

#ifndef CAMERA_HPP
#define CAMERA_HPP

class camera {
private:
  mat4 view;
  mat4 view_inverse;
  vec3 cached_p0;
  vec3 cached_pref;
  vec3 cached_up;

public:
  camera();
  camera(vec3 p0, vec3 pref, vec3 up);
  void MoveTo(vec3 delta_p0, vec3 delta_pref, vec3 delta_up);
  mat4* GetView();

  void Strafe(float delta);
  void Drive(float delta);
  void Elevate(float delta);
  void RotateX(float alpha);
  void RotateY(float alpha);
  void RotateZ(float alpha);
  void SetAngles(float horizontal_angle, float vertical_angle);

  void stream(std::ostream &strm);
};
std::ostream& operator<<(std::ostream &strm, const camera &cam);

#endif  /* CAMERA_HPP */