/* 
 * File:   off.hpp
 * Author: orvar
 *
 * Created on 31 January 2014, 17:04
 */

#include <string>
#include <vector>
#include "Vertex.hpp"

#ifndef OFF_HPP
#define	OFF_HPP

typedef struct {
    int numVertices;
    int numFaces;
    int numEdges;
} OFFHeader;

std::vector<Vertex*> readOFF(std::string fileName);
std::vector<Vertex*> parseOFF(std::string content);
OFFHeader parseOFFheader(std::string line);
Vertex* parseOFFvertex(std::string line);
std::vector<int> parseOFFface(std::string line);

#endif	/* OFF_HPP */

