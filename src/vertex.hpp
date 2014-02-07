/* 
 * File:   Vertex.hpp
 * Author: orvar
 *
 * Created on 31 January 2014, 16:59
 */

#ifndef VERTEX_HPP
#define	VERTEX_HPP

class Vertex {
public:
    Vertex(float x, float y, float z);
    Vertex(const Vertex& orig);
    virtual ~Vertex();
    
    float x, y, z;
private:
    
};

#endif	/* VERTEX_HPP */

