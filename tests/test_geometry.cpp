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
   * | 12 13 14 15 |   | 1 |
   */
  vec3 res = M * v;
  CHECK( res.x == 11.0 );
  CHECK( res.y == 39.0 );
  CHECK( res.z == 67.0 );
}

TEST_CASE( "inverse(M)", "[mat4]" ) {
  mat4 expected;
  mat4 M = mat4::Identity();
  mat4 inv = M.Inverse();

  // inv(I) == I
  for(int i = 0; i < 16; ++i) {
    CHECK( (M[i] - inv[i]) < 0.0001 );
  }


  M[0]  = 0.043927;
  M[1]  = 0.117831;
  M[2]  = 0.807404;
  M[3]  = 0.484102;
  M[4]  = 0.140768;
  M[5]  = 0.375091;
  M[6]  = 0.999290;
  M[7]  = 0.896548;
  M[8]  = 0.871029;
  M[9]  = 0.805784;
  M[10] = 0.988750;
  M[11] = 0.329027;
  M[12] = 0.435673;
  M[13] = 0.140597;
  M[14] = 0.858279;
  M[15] = 0.904856;
  expected[0]  = -0.36026;
  expected[1]  = -1.78631;
  expected[2]  =  0.57845;
  expected[3]  =  1.75231;
  expected[4]  = -2.31306;
  expected[5]  =  2.87194;
  expected[6]  =  0.55840;
  expected[7]  = -1.81112;
  expected[8]  =  2.95909;
  expected[9]  = -1.32179;
  expected[10] =  0.24590;
  expected[11] = -0.36289;
  expected[12] = -2.27391;
  expected[13] =  1.66758;
  expected[14] = -0.59852;
  expected[15] =  0.88707;

  inv = M.Inverse();
  for(int i = 0; i < 16; i++) {
    CHECK( inv[i] == expected[i] );
  }

}
