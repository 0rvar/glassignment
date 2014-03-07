#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

#include "geometry.hpp"
#include "off.hpp"

namespace OFF {

  veclist read(std::string fileName) {
    std::ifstream ifs(fileName.c_str());
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
     (std::istreambuf_iterator<char>()) );
    return parse(content);
  }

  veclist parse(std::string content) {
    std::vector<std::string> lines; 
    veclist vertices;
    std::vector <std::vector<int> > faces;
    veclist triangles;

    std::istringstream split(content); 
    for(std::string each; std::getline(split, each, '\n'); lines.push_back(each)){};

    //Todo better error handling
    if(lines.size() < 2 || lines[0].compare(0, 3, "OFF") != 0) {
      throw ParseException(std::string("Missing OFF header"), 0);
    }

    header h = parseHeader(lines[1]);

    if(lines.size() < uint(2 + h.numVertices + h.numFaces)) {
      throw ParseException(std::string("File ended unexpectedly"), lines.size());
    }

    for(int i = 2; i < h.numVertices + 2; i++) {
      vertices.push_back(parseVertex(lines[i]));
    }

    for(int i = 2 + h.numVertices; i < 2 + h.numVertices + h.numFaces; i++) {
      faces.push_back(parseFace(lines[i]));
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

    return normalize(triangles);
  }

  header parseHeader(std::string line) {
    std::istringstream tokens(line);
    int nV, nF, nE;
    tokens >> nV;
    tokens >> nF;
    tokens >> nE;

    header h;
    h.numVertices = nV;
    h.numFaces = nF;
    h.numEdges = nE;
    return h;
  }

  vec3 parseVertex(std::string line) {
    float x, y, z;
    std::istringstream tokens(line);
    tokens >> x >> y >> z;
    return vec3(x, y, z);
  }

  std::vector<int> parseFace(std::string line) {
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

  veclist normalize(veclist vertices) {
    float minX, maxX, minY, maxY, minZ, maxZ;

    veclist result = veclist();

    minX = minY = minZ = std::numeric_limits<float>::max();
    maxX = maxY = maxZ = std::numeric_limits<float>::min();
    for(veclist::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      vec3 v = *it;
      minX = minX < v.x? minX : v.x;
      minY = minY < v.y? minY : v.y;
      minZ = minZ < v.z? minZ : v.z;
      maxX = maxX > v.x? maxX : v.x;
      maxY = maxY > v.y? maxY : v.y;
      maxZ = maxZ > v.z? maxZ : v.z;
    }

    for(veclist::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      vec3 v = *it;
      //TODO: normalize
      //TODO: Revamp completely, [v,v,v,normal,...] ?
      result.push_back(v);
    }

    return result;
  }


  ParseException::ParseException(): line(0) {
    msg = std::string("Unknown parse error");
  }

  ParseException::ParseException(std::string m, int l) : msg(m), line(l) {}

  ParseException::~ParseException() throw(){}

  const char* ParseException::what() const throw (){
    return this->msg.c_str();
  }

}
