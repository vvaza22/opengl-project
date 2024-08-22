#include <shader/Shader.hpp>
#include <shader/FragmentShader.hpp>

#include <sstream>

FragmentShader::FragmentShader(const std::string& sourceCode) {
  create(sourceCode.c_str());
  compile();
}

FragmentShader::~FragmentShader() {
  glDeleteShader(shaderID);
}

void FragmentShader::create(const char* sourceCode) {
  // Returns unique shader identifier
  shaderID = glCreateShader(GL_FRAGMENT_SHADER);

  // Compile 1 shader, source code is a null terminated string
  glShaderSource(shaderID, 1, &sourceCode, nullptr);
}

void FragmentShader::compile() {
  glCompileShader(shaderID);

  // Check for compile errors
  int ok;
  char infoLog[512];

  // Pass an array of one integer as the last parameter, since we have one shader
  glGetShaderiv(shaderID, GL_COMPILE_STATUS, &ok);
  if(!ok) {
    glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);

    // Throw a runtime error
    std::ostringstream oss;
    oss << "Error: Could not compile fragment shader " << infoLog;
    throw new std::runtime_error(oss.str());
  }
}