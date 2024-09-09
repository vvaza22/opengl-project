#ifndef _ShaderProgram_
#define _ShaderProgram_

#include <shader/VertexShader.hpp>
#include <shader/FragmentShader.hpp>
#include <glm/glm.hpp>

class ShaderProgram {
public:
  ShaderProgram(VertexShader* v, FragmentShader* f);
  ~ShaderProgram();

  void use();
  GLuint GetID() {
    return shaderProgramID;
  }

  void SetMat4(const char* name, const float* mat);
  void SetVec3(const char* name, const float* vec);

protected:
  void create();
  void attach(Shader* shader);
  void link();

private:
  GLuint shaderProgramID;
  GLint getLoc(const char* name) const;
};

#endif
