#include <GL/glew.h>
#include <GL/freeglut.h>

#include "catch.hpp"

#include "geometry.hpp"
#include "camera.hpp"
#include "model.hpp"

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

TEST_CASE( "veclist(n) = {vec3{0}...}" , "[model::veclist]" ) {
  model::veclist v = model::veclist(1);
  REQUIRE( v.size() == 1 );

  CHECK( v[0].x == 0 );
  CHECK( v[0].y == 0 );
  CHECK( v[0].z == 0 );
}

TEST_CASE( "sizeof(uint) == sizeof(GLuint)" , "") {
  REQUIRE( sizeof(uint) == sizeof(GLuint) );
}
