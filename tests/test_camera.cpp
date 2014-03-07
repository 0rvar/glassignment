#include <cmath>

#include "catch.hpp"

#include "camera.hpp"
#include "geometry.hpp"

TEST_CASE( "Sanity checks", "[camera]" ) {
  vec3 p0   = vec3(2, 0, 2);
  vec3 pref = vec3(0, 0, -2);
  vec3 up   = vec3(0, 1, 0);
  camera cam = camera(p0, pref, up);

  mat4 v1 = *cam.GetView();
  cam.Strafe(0);
  cam.Drive(0);
  cam.Elevate(0);
  cam.RotateY(0);
  mat4 v2 = *cam.GetView();
  CHECK( abs(v1[0]  - v2[0])  < 0.000001 );
  CHECK( abs(v1[1]  - v2[1])  < 0.000001 );
  CHECK( abs(v1[2]  - v2[2])  < 0.000001 );
  CHECK( abs(v1[3]  - v2[3])  < 0.000001 );
  CHECK( abs(v1[4]  - v2[4])  < 0.000001 );
  CHECK( abs(v1[5]  - v2[5])  < 0.000001 );
  CHECK( abs(v1[6]  - v2[6])  < 0.000001 );
  CHECK( abs(v1[7]  - v2[7])  < 0.000001 );
  CHECK( abs(v1[8]  - v2[8])  < 0.000001 );
  CHECK( abs(v1[9]  - v2[9])  < 0.000001 );
  CHECK( abs(v1[10] - v2[10]) < 0.000001 );
  CHECK( abs(v1[11] - v2[11]) < 0.000001 );
  CHECK( abs(v1[12] - v2[12]) < 0.000001 );
  CHECK( abs(v1[13] - v2[13]) < 0.000001 );
  CHECK( abs(v1[14] - v2[14]) < 0.000001 );
  CHECK( abs(v1[15] - v2[15]) < 0.000001 );
  
}