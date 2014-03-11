#include <string>
#include <exception>
#include <vector>
#include "geometry.hpp"

#ifndef MODEL_HPP
#define	MODEL_HPP

namespace model {

  using veclist = std::vector<vec3>;

  typedef struct {
    veclist vertices;
    veclist normals;
    std::vector<uint> indices;
  } data;

  typedef struct {
    int numVertices;
    int numFaces;
    int numEdges;
  } header;

  data read(std::string fileName);
  data parse(std::string content);
  header parseHeader(std::string line);
  vec3 parseVertex(std::string line);
  std::vector<int> parseFace(std::string line);
  veclist normalize(veclist);

  class ParseException: public std::exception {
  private:
    std::string msg;

  public:
    ParseException();
    ParseException(std::string message, int line);
    virtual ~ParseException() throw();
    virtual const char* what() const throw();
    const int line;
  };

}

#endif	/* MODEL_HPP */

