/* 
 * File:   Matrix.hpp
 * Author: orvar
 *
 * Created on 05 February 2014, 09:43
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

class Matrix {
public:
    Matrix();
    Matrix operator+(const Matrix& other);
    Matrix operator*(const Matrix& other);
    float& operator[](unsigned int i){ return mat[i];}
    const float& operator[](unsigned int i)const{ return mat[i];}

private:
    float mat[16] = {0};
};

#endif  /* MATRIX_HPP */

