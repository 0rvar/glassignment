#ifndef SHADERTOOLS_HPP
#define SHADERTOOLS_HPP

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

namespace Shading {

  typedef struct {
          const char*  filename;
          GLenum       type;
          GLchar*      source;
  } Shader;

  char* readShaderSource(const char*);
  GLuint initProgramFromFiles(const char*, const char*);
  GLuint initProgram(const Shader vShader, const Shader fragShader);
  GLuint initProgram(const char* vShaderSource, const char* hShaderSource);

}

#endif // SHADERTOOLS_HPP
