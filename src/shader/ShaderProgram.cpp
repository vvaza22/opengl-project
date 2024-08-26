#include <shader/VertexShader.hpp>
#include <shader/FragmentShader.hpp>
#include <shader/ShaderProgram.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>

ShaderProgram::ShaderProgram(VertexShader* v, FragmentShader* f) {
  create();
  attach(v); // Vertex shader
  attach(f); // Fragment shader
  link(); // Can throw runtime error
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(shaderProgramID);
}

void ShaderProgram::create() {
  shaderProgramID = glCreateProgram();
}

void ShaderProgram::use() {
  glUseProgram(shaderProgramID);
}

void ShaderProgram::attach(Shader* shader) {
  glAttachShader(shaderProgramID, shader->GetID());
}

void ShaderProgram::SetMat4(const char* name, const glm::mat4& mat) {
  // 3rd argument is transpose, don't transpose the matrix
  glUniformMatrix4fv(getLoc(name), 1, GL_FALSE, glm::value_ptr(mat));
}

GLint ShaderProgram::getLoc(const char* name) const {
  return glGetUniformLocation(shaderProgramID, name);
}

void ShaderProgram::link() {
  glLinkProgram(shaderProgramID);

  // Check for link errors
  GLint ok;
  char infoLog[512];

  glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &ok);
  if(!ok) {
    glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);

    // Throw a runtime error
    std::ostringstream oss;
    oss << "Error: Could not link shader program " << infoLog;
    throw new std::runtime_error(oss.str());
  }
}