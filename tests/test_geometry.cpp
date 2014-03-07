#include <random>

#include "geometry.hpp"
#include "catch.hpp"

TEST_CASE( "Unit matrix times unit matrix is unit matrix", "[mat4]" ) {
  mat4 m = mat4::Identity();

  mat4 res = m*m;
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

TEST_CASE( "{1} * {1} = {4}", "[mat4]" ) {
  mat4 m1, m2, res;
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

TEST_CASE( "{random} * I = _", "[mat4, vec3]" ) {
  mat4 I, R, res;
  vec3 Rv, resv;
  I[0] = I[5] = I[10] = I[15] = 1;

  std::random_device rd;
  std::mt19937 e2(rd());
  std::uniform_real_distribution<> dist(0, 25);
  for(int i = 0; i < 16; i++) {
    R[i] = dist(e2);
  }
  Rv.x = dist(e2);
  Rv.y = dist(e2);
  Rv.z = dist(e2);

  res = I * R;
  for(int i = 0; i < 16; i++) {
    CHECK( res[i] == R[i] );
  }

  res = R * I;
  for(int i = 0; i < 16; i++) {
    CHECK( res[i] == R[i] );
  }

  resv = I * Rv;
  CHECK( Rv.x == resv.x );
  CHECK( Rv.y == resv.y );
  CHECK( Rv.z == resv.z );
}

TEST_CASE( "M * N", "[mat4]" ) {
  mat4 M, N, res;
  for(int i = 0; i < 16; i++) {
    M[i] = i;
  }
  res = M*M;
  CHECK( res[0]  == 56 );
  CHECK( res[1]  == 62 );
  CHECK( res[2]  == 68 );
  CHECK( res[3]  == 74 );
  CHECK( res[4]  == 152 );
  CHECK( res[5]  == 174 );
  CHECK( res[6]  == 196 );
  CHECK( res[7]  == 218 );
  CHECK( res[8]  == 248 );
  CHECK( res[9]  == 286 );
  CHECK( res[10] == 324 );
  CHECK( res[11] == 362 );
  CHECK( res[12] == 344 );
  CHECK( res[13] == 398 );
  CHECK( res[14] == 452 );
  CHECK( res[15] == 506 );

  N = M.Transpose();
  res = M*N;
  CHECK( res[0]  == 14 );
  CHECK( res[1]  == 38 );
  CHECK( res[2]  == 62 );
  CHECK( res[3]  == 86 );
  CHECK( res[4]  == 38 );
  CHECK( res[5]  == 126 );
  CHECK( res[6]  == 214 );
  CHECK( res[7]  == 302 );
  CHECK( res[8]  == 62 );
  CHECK( res[9]  == 214 );
  CHECK( res[10] == 366 );
  CHECK( res[11] == 518 );
  CHECK( res[12] == 86 );
  CHECK( res[13] == 302 );
  CHECK( res[14] == 518 );
  CHECK( res[15] == 734 );
}

TEST_CASE( "M * v", "[mat4, vec3]" ) {
  mat4 M;
  vec3 v = vec3(1, 2, 3);

  for(int i = 0; i < 16; i++) {
    M[i] = i;
  }

  /* | 0  1  2  3  |   | 1 |
   * | 4  5  6  7  | x | 2 |
   * | 8  9  10 11 |   | 3 |
   * | 12 13 14 15 |   | 0 |
   */
  vec3 res = M * v;
  CHECK( res.x == 8.0 );
  CHECK( res.y == 32.0 );
  CHECK( res.z == 56.0 );
}
