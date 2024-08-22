#ifndef _Model_
#define _Model_

#include <glad/glad.h>
#include <structures/FloatArray.hpp>

class Model {
public:
  Model(FloatArray* array);
  ~Model();

  GLuint VertexArrayID() const {
    return vertexArrayObjectID;
  }

  void draw();

private:
  GLuint vertexArrayObjectID;
  GLuint vertexBufferObjectID;
  int length;

  // VAO
  void createVertexArrayObject();
  void bindVertexArrayObject();
  void unbindVertexArrayObject();

  // VBO
  void createVertexBufferObject();
  void bindVertexBufferObject();
  void sendDataToVertexBufferObject(int length, const float* array);
  void unbindVertexBufferObject();
};

#endif