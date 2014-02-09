#include "catch.hpp"

#include "vertex.hpp"
#include "transform.hpp"

TEST_CASE( "Vertex objects are laid out as 3 floats in memory", "[vertex]" ) {
  REQUIRE( sizeof(Vertex) == 3 * sizeof(float) );
}

TEST_CASE( "Matrices and transforms are laid out as mat4 in memory", "[matrix, transform]" ) {
  float mat44[16];
  REQUIRE( sizeof(Transform) == sizeof(Matrix) );
  REQUIRE( sizeof(Matrix) == sizeof(mat44) );
}

TEST_CASE( "Matrices are initialized to 0", "[matrix]") {
  Matrix m;
  for(int i = 0; i < 16; i++) {
    REQUIRE( m[i] == 0 );
  }
}
