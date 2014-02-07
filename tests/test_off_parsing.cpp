/* 
 * File:   offtest.cpp
 * Author: orvar
 *
 * Created on 31-Jan-2014, 17:11:38
 */

#include <stdlib.h>
#include <iostream>
#include "off.hpp"

#include "catch.hpp"

/*
 * Simple C++ Test Suite
 */

 TEST_CASE( "OFF face lines are parsed", "[off]" ) {
  std::string line ("5 1 2 3 4 5");
  std::vector<int> r = parseOFFface(line);

  REQUIRE( r.size() == 5 );
  REQUIRE( r[0] == 1 );
  REQUIRE( r[1] == 2 );
  REQUIRE( r[2] == 3 );
  REQUIRE( r[3] == 4 );
  REQUIRE( r[4] == 5 );
}

TEST_CASE( "OFF header line is parsed", "[off]" ) {
  std::string line ("8 6 24");
  OFFHeader h = parseOFFheader(line);

  REQUIRE( h.numVertices == 8 );
  REQUIRE( h.numFaces == 6 );
  REQUIRE( h.numEdges == 24 );
}

TEST_CASE( "OFF vertex lines are parsed", "[off]" ) {
  std::string line ("6 7 8");
  Vertex result = parseOFFvertex(line);

  CHECK( result.x == 6.0 );
  CHECK( result.y == 7.0 );
  CHECK( result.z == 8.0 );
}

TEST_CASE( "OFF is parsed", "[off]" ) {
  std::string content ("OFF\n8 6 24\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n4 0 1 3 2\n4 2 3 7 6\n4 4 6 7 5\n4 0 4 5 1\n4 1 5 7 3\n4 0 2 6 4");
  std::vector<Vertex> result = parseOFF(content);

  REQUIRE( result.size() == 12*3 );
}

TEST_CASE( "Invalid files are handled", "[off]" ) {

  SECTION( "There is no OFF header" ) {
    std::string content ("8 6 24\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n4 0 1 3 2\n4 2 3 7 6\n4 4 6 7 5\n4 0 4 5 1\n4 1 5 7 3\n4 0 2 6 4");
    REQUIRE_THROWS_AS(parseOFF(content), OFFParseException);
    try {
      parseOFF(content);
    } catch(OFFParseException &e) {
      REQUIRE(e.line == 0);
    }
  }
  
  SECTION( "The file is too short" ) {
    std::string content ("OFF\n8 6 24\n0 0 0\n0 0 1\n0 1 0\n0 1 1\n1 0 0\n1 0 1\n1 1 0\n1 1 1\n4 0 1 3 2\n4 2 3 7 6");
    REQUIRE_THROWS_AS(parseOFF(content), OFFParseException);
    try {
      parseOFF(content);
    } catch(OFFParseException &e) {
      REQUIRE(e.line == 12);
    }
  }
  
}
