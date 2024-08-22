#include <shader/VertexShader.hpp>
#include <shader/FragmentShader.hpp>
#include <shader/ShaderProgram.hpp>
#include <shader/ShaderFactory.hpp>

ShaderProgram* ShaderFactory::CreateShaderProgram(const std::string& vertexPath, const std::string& fragmentPath) {
  std::string vertexSource = filesystem::ReadTextFile(vertexPath);
  std::string fragmentSource = filesystem::ReadTextFile(fragmentPath);

  VertexShader vShader(vertexSource);
  FragmentShader fShader(fragmentSource);

  ShaderProgram* shaderProgram = new ShaderProgram(&vShader, &fShader);

  return shaderProgram;
}