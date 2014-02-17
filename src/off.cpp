#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <assert.h>

#include "geometry.hpp"
#include "off.hpp"

std::vector<vec3> readOFF(std::string fileName) {
  std::ifstream ifs(fileName.c_str());
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()) );
  return parseOFF(content);
}

std::vector<vec3> parseOFF(std::string content) {
  std::vector<std::string> lines; 
  std::vector<vec3> vertices;
  std::vector <std::vector<int> > faces;
  std::vector<vec3> triangles;

  std::istringstream split(content); 
  for(std::string each; std::getline(split, each, '\n'); lines.push_back(each));
  
  //Todo better error handling
  if(lines.size() < 2 || lines[0].compare(0, 3, "OFF") != 0) {
    throw OFFParseException(std::string("Missing OFF header"), 0);
  }
  
  OFFHeader h = parseOFFheader(lines[1]);

  if(lines.size() < uint(2 + h.numVertices + h.numFaces)) {
    throw OFFParseException(std::string("File ended unexpectedly"), lines.size());
  }

  for(int i = 2; i < h.numVertices + 2; i++) {
    vertices.push_back(parseOFFvertex(lines[i]));
  }

  for(int i = 2 + h.numVertices; i < 2 + h.numVertices + h.numFaces; i++) {
    faces.push_back(parseOFFface(lines[i]));
  }
  
  // wow, such expressiveness
  for(std::vector <std::vector<int> >::iterator it = faces.begin(); it != faces.end(); ++it) {
      std::vector<int> face = *it;
      for(uint i = 2; i < face.size(); i++) {
        triangles.push_back(vertices[face[0]]);
        triangles.push_back(vertices[face[i-1]]);
        triangles.push_back(vertices[face[i]]);
      }
  }
  
  return triangles;
}

OFFHeader parseOFFheader(std::string line) {
  std::istringstream tokens(line);
  int nV, nF, nE;
  tokens >> nV;
  tokens >> nF;
  tokens >> nE;
  
  OFFHeader h;
  h.numVertices = nV;
  h.numFaces = nF;
  h.numEdges = nE;
  return h;
}

vec3 parseOFFvertex(std::string line) {
  float x, y, z;
  std::istringstream tokens(line);
  tokens >> x >> y >> z;
  return vec3(x, y, z);
}

std::vector<int> parseOFFface(std::string line) {
  std::vector<int> face;
  int size;
  std::istringstream tokens(line);
  tokens >> size;
  for(int i = 0; i < size; i++) {
    int v;
    tokens >> v;
    face.push_back(v);
  }
  return face;
}

OFFParseException::OFFParseException(): line(0) {
  msg = std::string("Unknown parse error");
}

OFFParseException::OFFParseException(std::string m, int l) : msg(m), line(l) {}

OFFParseException::~OFFParseException() throw(){}

const char* OFFParseException::what() const throw (){
  return this->msg.c_str();
}