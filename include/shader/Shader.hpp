#ifndef _Shader_
#define _Shader_

#include <glad/glad.h>

class Shader {
public:
  GLuint GetID() {
    return shaderID;
  }
protected:
  GLuint shaderID;

  virtual void create(const char* sourceCode) = 0;
  virtual void compile() = 0;
};

#endif