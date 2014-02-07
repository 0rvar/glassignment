#include "catch.hpp"

#include "vertex.hpp"

TEST_CASE( "Vertex objects are laid out as 3 floats in memory", "[vertex]" ) {
  REQUIRE( sizeof(Vertex)  == 3 * sizeof(float) );
}
