#include <random>

#include "matrix.hpp"
#include "catch.hpp"

TEST_CASE( "Unit matrix timer unit matrix is unit matrix", "[matrix]" ) {
  Matrix m;
  m[0] = 1;
  m[5] = 1;
  m[10] = 1;
  m[15] = 1;

  Matrix res = m*m;
  CHECK( res[0]  == 1 );
  CHECK( res[1]  == 0 );
  CHECK( res[2]  == 0 );
  CHECK( res[3]  == 0 );
  CHECK( res[4]  == 0 );
  CHECK( res[5]  == 1 );
  CHECK( res[6]  == 0 );
  CHECK( res[7]  == 0 );
  CHECK( res[8]  == 0 );
  CHECK( res[9]  == 0 );
  CHECK( res[10] == 1 );
  CHECK( res[11] == 0 );
  CHECK( res[12] == 0 );
  CHECK( res[13] == 0 );
  CHECK( res[14] == 0 );
  CHECK( res[15] == 1 );
}

TEST_CASE( "{1} * {1} = {4}", "[matrix]" ) {
  Matrix m1, m2, res;
  for(int i = 0; i < 16; i++) {
    m1[i] = m2[i] = 1;
  }
  res = m1*m2;
  CHECK( res[0]  == 4 );
  CHECK( res[1]  == 4 );
  CHECK( res[2]  == 4 );
  CHECK( res[3]  == 4 );
  CHECK( res[4]  == 4 );
  CHECK( res[5]  == 4 );
  CHECK( res[6]  == 4 );
  CHECK( res[7]  == 4 );
  CHECK( res[8]  == 4 );
  CHECK( res[9]  == 4 );
  CHECK( res[10] == 4 );
  CHECK( res[11] == 4 );
  CHECK( res[12] == 4 );
  CHECK( res[13] == 4 );
  CHECK( res[14] == 4 );
  CHECK( res[15] == 4 );
}

TEST_CASE( "{random} * I = _", "[matrix]" ) {
  Matrix I, R, res;
  I[0] = I[5] = I[10] = I[15] = 1;

  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> dist(0, 25);
  for(int i = 0; i < 16; i++) {
    R[i] = dist(e2);
  }

  res = I * R;
  for(int i = 0; i < 16; i++) {
    CHECK( res[i] == R[i] );
  }

  res = R * I;
  for(int i = 0; i < 16; i++) {
    CHECK( res[i] == R[i] );
  }
}
