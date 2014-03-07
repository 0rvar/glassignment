#include "catch.hpp"

#include "geometry.hpp"
#include "camera.hpp"

TEST_CASE( "Vertex objects are laid out as 3 floats in memory", "[vec3]" ) {
  REQUIRE( sizeof(vec3) == 3 * sizeof(float) );
}

TEST_CASE( "Matrices and transforms are laid out as mat4 in memory", "[mat4,transform]" ) {
  float _mat44[16];
  REQUIRE( sizeof(mat4) == sizeof(_mat44) );
}

TEST_CASE( "Matrices are initialized to 0", "[mat4]" ) {
  mat4 m;
  for(int i = 0; i < 16; i++) {
    REQUIRE( m[i] == 0 );
  }
}

TEST_CASE( "camera.view size == mat4 size", "[camera,mat4]" ) {
  camera cam;
  REQUIRE( sizeof(*cam.GetView()) == sizeof(mat4) );
}
