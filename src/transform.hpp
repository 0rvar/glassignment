/* 
 * File:   Transform.hpp
 * Author: orvar
 *
 * Created on 05 February 2014, 09:43
 */

#include "matrix.hpp"

#ifndef TRANSFORM_HPP
#define	TRANSFORM_HPP

class Transform {
public:
    Transform();
    Transform Translate(float x, float y, float z);
    Matrix GetMatrix();
private:
    Matrix matrix;
};

#endif	/* TRANSFORM_HPP */

