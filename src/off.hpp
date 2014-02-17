/* 
 * File:   off.hpp
 * Author: orvar
 *
 * Created on 31 January 2014, 17:04
 */

#include <string>
#include <exception>
#include <vector>
#include "geometry.hpp"

#ifndef OFF_HPP
#define	OFF_HPP

typedef struct {
    int numVertices;
    int numFaces;
    int numEdges;
} OFFHeader;

std::vector<vec3> readOFF(std::string fileName);
std::vector<vec3> parseOFF(std::string content);
OFFHeader parseOFFheader(std::string line);
vec3 parseOFFvertex(std::string line);
std::vector<int> parseOFFface(std::string line);


class OFFParseException: public std::exception {
  private:
    std::string msg;

  public:
    OFFParseException();
    OFFParseException(std::string message, int line);
    virtual ~OFFParseException() throw();
    virtual const char* what() const throw();
    const int line;
};

#endif	/* OFF_HPP */

