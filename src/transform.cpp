#include "transform.hpp"
#include "matrix.hpp"

Transform::Transform() {
  for(int i = 0; i < 16; i++) {
    if(i / 4 == i % 4) {
      matrix[i] = 1;
    } else {
      matrix[i] = 0;
    }
  }
}

Transform Transform::Translate(float x, float y, float z) {
  Transform r;
  r.matrix[3] = x;
  r.matrix[7] = y;
  r.matrix[11] = z;
  r.matrix = r.matrix * matrix;

  return r;
}

Transform Transform::Scale(float factor) {
  Transform r;
  r.matrix[0] = r.matrix[5] = r.matrix[10] = factor;
  r.matrix[15] = 1;
  r.matrix = r.matrix * matrix;

  return r;
}

Matrix Transform::GetMatrix() {
  return matrix;
}

Transform Transform::Transpose() {
  Transform r;
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      r.matrix[row*4+col] = matrix[col*4+row];
    }
  }
  return r;
}
