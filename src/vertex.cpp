/* 
 * File:   Vertex.cpp
 * Author: orvar
 * 
 * Created on 31 January 2014, 16:59
 */

#include "vertex.hpp"

Vertex Vertex_(float nx, float ny, float nz) {
  Vertex v;
  v.x = nx;
  v.y = ny;
  v.z = nz;
  return v;
}

std::ostream& operator<<(std::ostream &strm, const struct _v &v) {
  strm << "Vertex(" << v.x << ", " << v.y << ", " << v.z << ")";
  return strm;
}
