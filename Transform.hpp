/* 
 * File:   Transform.hpp
 * Author: orvar
 *
 * Created on 05 February 2014, 09:43
 */

#ifndef TRANSFORM_HPP
#define	TRANSFORM_HPP

class Transform {
public:
    Transform();
    float* GetMatrix();
    Transform* Translate(float x, float y, float z);
    
private:
    float mat[16];
};

#endif	/* TRANSFORM_HPP */

