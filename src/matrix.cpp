#include "matrix.hpp"

Matrix::Matrix() {}

Matrix Matrix::operator+(const Matrix& other) {
  Matrix result;
  for(int i = 0; i < 16; i++) {
    result[i] = mat[i] + other[i];
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& other) {
  Matrix result;
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      for(int step = 0; step < 4; step++) {
        result[row*4 + col] += mat[row*4 + step] * mat[step*4 + col];
      }
    }
  }
  return result;
}
