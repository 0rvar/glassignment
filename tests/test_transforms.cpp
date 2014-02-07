#include "catch.hpp"

#include "transform.hpp"

TEST_CASE( "New transform is identity matrix", "[transform]" ) {
  Transform t;
  float *m = t.GetMatrix();
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
