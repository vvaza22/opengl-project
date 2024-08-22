#ifndef _ShaderProgram_
#define _ShaderProgram_

#include <shader/VertexShader.hpp>
#include <shader/FragmentShader.hpp>

class ShaderProgram {
public:
  ShaderProgram(VertexShader* v, FragmentShader* f);
  ~ShaderProgram();

  void use();
  GLuint GetID() {
    return shaderProgramID;
  }

protected:
  void create();
  void attach(Shader* shader);
  void link();

private:
  GLuint shaderProgramID;
};

#endif