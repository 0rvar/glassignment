#include "catch.hpp"

#include "transform.hpp"

TEST_CASE( "New transform is identity matrix", "[transform]" ) {
  Transform t;
  Matrix m = t.GetMatrix();
  REQUIRE( m[0]  == 1 );
  REQUIRE( m[1]  == 0 );
  REQUIRE( m[2]  == 0 );
  REQUIRE( m[3]  == 0 );
  REQUIRE( m[4]  == 0 );
  REQUIRE( m[5]  == 1 );
  REQUIRE( m[6]  == 0 );
  REQUIRE( m[7]  == 0 );
  REQUIRE( m[8]  == 0 );
  REQUIRE( m[9]  == 0 );
  REQUIRE( m[10] == 1 );
  REQUIRE( m[11] == 0 );
  REQUIRE( m[12] == 0 );
  REQUIRE( m[13] == 0 );
  REQUIRE( m[14] == 0 );
  REQUIRE( m[15] == 1 );
}

TEST_CASE( "Translate", "[transform]" ) {
  Transform t;
  Matrix m = t.Translate(1, 2, 3).GetMatrix();
  CHECK( m[0]  == 1 );
  CHECK( m[1]  == 0 );
  CHECK( m[2]  == 0 );
  CHECK( m[3]  == 1 );
  CHECK( m[4]  == 0 );
  CHECK( m[5]  == 1 );
  CHECK( m[6]  == 0 );
  CHECK( m[7]  == 2 );
  CHECK( m[8]  == 0 );
  CHECK( m[9]  == 0 );
  CHECK( m[10] == 1 );
  CHECK( m[11] == 3 );
  CHECK( m[12] == 0 );
  CHECK( m[13] == 0 );
  CHECK( m[14] == 0 );
  CHECK( m[15] == 1 );
}

TEST_CASE( "Scale", "[transform]" ) {
  Transform t;
  Matrix m;
  float factor = 0.5;

  m = t.Scale(factor).GetMatrix();
  CHECK( m[0]  == factor );
  CHECK( m[1]  == 0 );
  CHECK( m[2]  == 0 );
  CHECK( m[3]  == 0 );
  CHECK( m[4]  == 0 );
  CHECK( m[5]  == factor );
  CHECK( m[6]  == 0 );
  CHECK( m[7]  == 0 );
  CHECK( m[8]  == 0 );
  CHECK( m[9]  == 0 );
  CHECK( m[10] == factor );
  CHECK( m[11] == 0 );
  CHECK( m[12] == 0 );
  CHECK( m[13] == 0 );
  CHECK( m[14] == 0 );
  CHECK( m[15] == 1 );
}