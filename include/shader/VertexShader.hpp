#ifndef _VertexShader_
#define _VertexShader_

#include <shader/Shader.hpp>

#include <string>

class VertexShader : public Shader {
public:
  VertexShader(const std::string& sourceCode);
  ~VertexShader();
protected:
  void create(const char* sourceCode);
  void compile();
};

#endif