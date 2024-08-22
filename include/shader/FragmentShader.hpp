#ifndef _FragmentShader_
#define _FragmentShader_

#include <shader/Shader.hpp>

#include <string>

class FragmentShader : public Shader {
public:
  FragmentShader(const std::string& sourceCode);
  ~FragmentShader();
protected:
  void create(const char* sourceCode);
  void compile();
};

#endif