/* 
 * File:   Vertex.hpp
 * Author: orvar
 *
 * Created on 31 January 2014, 16:59
 */

#include <ostream>

#ifndef VERTEX_HPP
#define	VERTEX_HPP

typedef struct _v {
  float x, y, z;
} Vertex;

Vertex Vertex_(float x, float y, float z);

std::ostream& operator<<(std::ostream &strm, const struct _v &v);

#endif	/* VERTEX_HPP */

