#ifndef _ShaderFactory_
#define _ShaderFactory_

#include <shader/ShaderProgram.hpp>
#include <filesystem/Reader.hpp>

class ShaderFactory {
public:
  ShaderProgram* CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath);
};

#endif