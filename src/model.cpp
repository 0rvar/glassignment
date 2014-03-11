#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

#include "geometry.hpp"
#include "model.hpp"

namespace model {

  data read(std::string fileName) {
    std::ifstream ifs(fileName.c_str());
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
     (std::istreambuf_iterator<char>()) );
    return parse(content);
  }

  data parse(std::string content) {
    std::vector<std::string> lines; 
    veclist vertices;
    std::vector <std::vector<int> > faces;

    veclist face_normals;
    veclist vertex_normals;
    std::vector<uint> indices;

    // veclist triangles;
    // veclist triangle_normals;

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

    vertex_normals = veclist(h.numVertices);

    // Parse faces, calculate face normals
    for(int i = 2 + h.numVertices; i < 2 + h.numVertices + h.numFaces; i++) {
      std::vector<int> face = parseFace(lines[i]);
      faces.push_back(face);

      vec3 v1 = vertices[face[1]] - vertices[face[0]];
      vec3 v2 = vertices[face[2]] - vertices[face[0]];
      face_normals.push_back(v1.cross(v2));
    }

    // A vertex normal is the average of all connected faces' normals,
    //  so add them all up...
    for(auto it = faces.begin(); it != faces.end(); ++it) {
      std::vector<int> face = *it;
      int i = std::distance(faces.begin(), it);
      vec3 face_normal = face_normals[i];
      
      for(auto it2 = face.begin(); it2 != face.end(); ++it2) {
        int vertex_index = *it2;
        vertex_normals[vertex_index] = vertex_normals[vertex_index] + face_normal;
      }
    }
    // ... and then normalize
    for(uint i = 0; i < vertex_normals.size(); ++i) {
      vertex_normals[i] = vertex_normals[i].normalize();
    }

    // Generate triangle index array 
    for(auto it = faces.begin(); it != faces.end(); ++it) {
      std::vector<int> face = *it;

      for(uint i = 2; i < face.size(); i++) {
        indices.push_back(face[0]);
        indices.push_back(face[i-1]);
        indices.push_back(face[i]);
      }

      // for(uint i = 2; i < face.size(); i++) {
      //   triangles.push_back(vertices[face[0]]);
      //   triangles.push_back(vertices[face[i-1]]);
      //   triangles.push_back(vertices[face[i]]);
      //   triangle_normals.push_back(vertex_normals[face[0]]);
      //   triangle_normals.push_back(vertex_normals[face[i-1]]);
      //   triangle_normals.push_back(vertex_normals[face[i]]);
      // }
    }

    data m;
    m.vertices = normalize(vertices);
    m.normals = vertex_normals;
    m.indices = indices;
    return m;
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
    veclist result = veclist();
    float maxLength = 0;

    for(veclist::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      vec3 v = *it;
      float l = v.length();
      if(l > maxLength) {
        maxLength = l;
      }
    }

    for(veclist::iterator it = vertices.begin(); it != vertices.end(); ++it) {
      vec3 v = *it;
      //TODO: normalize
      //TODO: Revamp completely, [v,v,v,normal,...] ?
      result.push_back(v * (1/maxLength));
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
